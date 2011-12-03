#include <stdint.h>
#include <device/pci_def.h>
#include <device/pci_ids.h>
#include <arch/io.h>
#include <device/pnp_def.h>
#include <arch/romcc_io.h>
#include <arch/hlt.h>
#include <stdlib.h>
#include <console/console.h>
#include "northbridge/dmp/vortex86mx/raminit.h"
#include "cpu/x86/mtrr/earlymtrr.c"
#include "cpu/x86/bist.h"
#include "pc80/udelay_io.c"
#include "lib/delay.c"
#include "superio/winbond/w83627hf/early_serial.c"
#include "cpu/x86/lapic/boot_cpu.c"
#include "lib/debug.c"

/* Predefined SPD values, because mainboard doesn't have SPD */
#include "spd_table.h"
#include <spd.h>

static int spd_read_byte(unsigned device, unsigned address)
{
	int i;

	if (device == DIMM0) {
		for (i=0; i < (ARRAY_SIZE(spd_table)); i++) {
			if (spd_table[i].address == address) {
				return spd_table[i].data;
			}
		}
	}

	/* returns 0xFF on any failures */
	return 0xFF;
}


#include "northbridge/dmp/vortex86mx/raminit.c"

#define CONFIG_SERIAL_DEV PNP_DEV(0x2e, W83627HF_SP1)

static void enable_mainboard_devices(void)
{
	device_t dev;

	dev = pci_locate_device_on_bus(PCI_ID(PCI_VENDOR_ID_DMP,
				       PCI_DEVICE_ID_DMP_VORTEX86MX), 0);

	if (dev == PCI_DEV_INVALID) {
		die("Southbridge not found!!!\n");
	}
	pci_write_config8(dev, 0x50, 0x80);
	pci_write_config8(dev, 0x51, 0x1f);
    dev += 0x100; /* ICKY */

	pci_write_config8(dev, 0x04, 7);
	pci_write_config8(dev, 0x40, 3);
	pci_write_config8(dev, 0x42, 0);
	pci_write_config8(dev, 0x3c, 0xe);
	pci_write_config8(dev, 0x3d, 0);
}

static void enable_shadow_ram(void)
{
	device_t dev = 0; /* no need to look up 0:0.0 */
	unsigned char shadowreg;
	/* dev 0 for southbridge */
	shadowreg = pci_read_config8(dev, 0x63);
	/* 0xf0000-0xfffff */
	shadowreg |= 0x30;
	pci_write_config8(dev, 0x63, shadowreg);
}

static void main(unsigned long bist)
{
	device_t dev;

	/* Enable VGA; 32MB buffer. */
	pci_write_config8(0, 0xe1, 0xdd);

	/*
	 * Disable the firewire stuff, which apparently steps on IO 0+ on
	 * reset. Doh!
	 */
	dev = pci_locate_device_on_bus(PCI_ID(PCI_VENDOR_ID_VIA,
				PCI_DEVICE_ID_VIA_6305), 0);
	if (dev != PCI_DEV_INVALID)
		pci_write_config8(dev, 0x15, 0x1c);

	w83627hf_enable_serial(CONSOLE_SERIAL_DEV, CONFIG_TTYS0_BASE);
	console_init();

	/* Halt if there was a built in self test failure */
	report_bist_failure(bist);

	// init_timer();

	post_code(0x05);

	print_debug(" Enabling mainboard devices\n");
	enable_mainboard_devices();

	print_debug(" Enabling shadow ram\n");
	enable_shadow_ram();

	ddr_ram_setup((const struct mem_controller *)0);

	if (bist == 0)
		early_mtrr_init();

	//dump_pci_devices();
}
