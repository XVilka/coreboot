#include <console/console.h>
#include <arch/io.h>
#include <stdint.h>
#include <device/device.h>
#include <device/pci.h>
#include <device/hypertransport.h>
#include <device/pci_ids.h>
#include <stdlib.h>
#include <string.h>
#include <bitops.h>
#include <cpu/cpu.h>
#include <cpu/x86/mtrr.h>
#include <cpu/x86/msr.h>
#include "chip.h"
#include "northbridge.h"

static void northbridge_init(device_t dev)
{
	device_t fb_dev;
	unsigned long fb;
	unsigned char c;

	printk(BIOS_DEBUG, "Vortex86MX northbridge early init ...\n");
	
	c = pci_read_config8(dev, NB_REG_PMCR);
	c &= ~0xf0;
	c |= 0x05;
	pci_write_config8(dev, NB_REG_PMCR, c);
	pci_write_config8(dev, NB_REG_MAR, 0);
	c = pci_read_config8(dev, NB_REG_MBR);
	c &= 0xfc;
	pci_write_config8(dev, NB_REG_MBR);
	pci_write_config8(dev, NB_REG_SMM, 0);
	c = pci_read_config8(dev, NB_REG_SDRAM_MCR);
	c &= ~0xf9;
	c |= 0x06;
	pci_write_config8(dev, NB_REG_SDRAM_MCR, c);
	pci_write_config8(dev, NB_REG_MRR, 0);
	c = pci_read_config8(dev, NB_REG_CPU_DCR + 1);
	c &= ~0xfb;
	c |= 0x04;
	pci_write_config8(dev, NB_REG_CPU_DCR + 1, c);
	c = pci_read_config8(dev, NB_REG_PACR);
	c &= ~0xfc;
	c |= 0x01;
	pci_write_config8(dev, NB_REG_PACR, c);

	pci_write_config16(dev, NB_REG_SPI_BASE, 0xfc01);
	pci_write_config32(dev, NB_REG_BUF_SC, 0x83e7cf9f);

}

static void nullfunc(device_t dev)
{
	/* Nothing to do */
}

static struct device_operations northbridge_operations = {
	.read_resources   = nullfunc,
	.set_resources    = pci_dev_set_resources,
	.enable_resources = pci_dev_enable_resources,
	.init             = northbridge_init
};

static const struct pci_driver northbridge_driver __pci_driver = {
	.ops = &northbridge_operations,
	.vendor = PCI_VENDOR_ID_DMP,
	.device = PCI_DEVICE_ID_DMP_VORTEX86_PCI,
};

static void agp_init(device_t dev)
{
	printk(BIOS_DEBUG, "DMP Vortex86MX AGP init ...\n");

}

static struct device_operations agp_operations = {
	.read_resources   = nullfunc,
	.set_resources    = pci_dev_set_resources,
	.enable_resources = pci_bus_enable_resources,
	.init             = agp_init,
	.scan_bus         = pci_scan_bridge,
	.ops_pci          = 0,
};

static const struct pci_driver agp_driver __pci_driver = {
	.ops = &agp_operations,
	.vendor = PCI_VENDOR_ID_DMP,
	.device = PCI_DEVICE_ID_DMP_VORTEX86MX_VGA,
};

#if CONFIG_WRITE_HIGH_TABLES==1
#include <cbmem.h>
#endif

static void pci_domain_set_resources(device_t dev)
{
	static const uint8_t ramregs[] = {0x5a, 0x5b, 0x5c, 0x5d };
	device_t mc_dev;
        uint32_t pci_tolm;

	printk(BIOS_SPEW, "Entering vortex86mx pci_domain_set_resources.\n");

        pci_tolm = find_pci_tolm(dev->link_list);
	mc_dev = dev->link_list->children;
	if (mc_dev) {
		unsigned long tomk, tolmk;
		unsigned char rambits;
		int i, idx;

		for(rambits = 0, i = 0; i < ARRAY_SIZE(ramregs); i++) {
			unsigned char reg;
			reg = pci_read_config8(mc_dev, ramregs[i]);
			/* these are ENDING addresses, not sizes.
			 * if there is memory in this slot, then reg will be > rambits.
			 * So we just take the max, that gives us total.
			 * We take the highest one to cover for once and future coreboot
			 * bugs. We warn about bugs.
			 */
			if (reg > rambits)
				rambits = reg;
			if (reg < rambits)
				printk(BIOS_ERR, "ERROR! register 0x%x is not set!\n",
					ramregs[i]);
		}
		printk(BIOS_DEBUG, "I would set ram size to 0x%x Kbytes\n", (rambits)*16*1024);
		tomk = rambits*16*1024 - 32768;
		/* Compute the top of Low memory */
		tolmk = pci_tolm >> 10;
		if (tolmk >= tomk) {
			/* The PCI hole does does not overlap the memory.
			 */
			tolmk = tomk;
		}

#if CONFIG_WRITE_HIGH_TABLES == 1
		high_tables_base = (tolmk * 1024) - HIGH_MEMORY_SIZE;
		high_tables_size = HIGH_MEMORY_SIZE;
		printk(BIOS_DEBUG, "tom: %lx, high_tables_base: %llx, high_tables_size: %llx\n",
						tomk*1024, high_tables_base, high_tables_size);
#endif

		/* Report the memory regions */
		idx = 10;
		ram_resource(dev, idx++, 0, 640);		/* first 640k */
		ram_resource(dev, idx++, 768, tolmk - 768);	/* leave a hole for vga */
	}
	assign_resources(dev->link_list);
}

static struct device_operations pci_domain_ops = {
        .read_resources   = pci_domain_read_resources,
        .set_resources    = pci_domain_set_resources,
        .enable_resources = NULL,
        .init             = NULL,
        .scan_bus         = pci_domain_scan_bus,
};

static void cpu_bus_init(device_t dev)
{
        initialize_cpus(dev->link_list);
}

static void cpu_bus_noop(device_t dev)
{
}

static struct device_operations cpu_bus_ops = {
        .read_resources   = cpu_bus_noop,
        .set_resources    = cpu_bus_noop,
        .enable_resources = cpu_bus_noop,
        .init             = cpu_bus_init,
        .scan_bus         = 0,
};

static void enable_dev(struct device *dev)
{
	printk(BIOS_SPEW, "In vortex86mx enable_dev for device %s.\n", dev_path(dev));

        /* Set the operations if it is a special bus type */
        if (dev->path.type == DEVICE_PATH_PCI_DOMAIN) {
                dev->ops = &pci_domain_ops;
		pci_set_method(dev);
        }
        else if (dev->path.type == DEVICE_PATH_APIC_CLUSTER) {
                dev->ops = &cpu_bus_ops;
        }
}

struct chip_operations northbridge_dmp_vortex86mx_ops = {
	CHIP_NAME("DMP Vortex86MX Northbridge")
	.enable_dev = enable_dev,
};
