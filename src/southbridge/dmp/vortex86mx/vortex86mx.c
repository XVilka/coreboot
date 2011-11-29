#include <console/console.h>
#include <device/device.h>
#include <device/pci.h>
#include <device/pci_ops.h>
#include <device/pci_ids.h>
#include <pc80/keyboard.h>
#include <pc80/i8259.h>
#include "chip.h"
#include "vortex86mx.h"

// TODO: Add FCDC 8051 firmware downloading control

static void keyboard_on(struct device *dev)
{
	u8 regval;

	regval = pci_read_config8(dev, 0x51);
	regval |= 0x05;
	regval &= 0xfd;
	pci_write_config8(dev, 0x51, regval);

	pc_keyboard_init(0);
}

#ifdef UNUSED_CODE
void dump_south(device_t dev0)
{
	int i,j;

	for(i = 0; i < 256; i += 16) {
		printk(BIOS_DEBUG, "0x%x: ", i);
		for(j = 0; j < 16; j++) {
			printk(BIOS_DEBUG, "%02x ", pci_read_config8(dev0, i+j));
		}
		printk(BIOS_DEBUG, "\n");
	}
}
#endif

// TODO: add LPC SERVO SPI Init
// Check Chip ID

static void vortex86mx_sb_enable(struct device *dev)
{
	unsigned char c;
	u16 vendor, model;

	vendor = pci_read_config16(dev, 0);
	model = pci_read_config16(dev, 0x2); // must be 0x6063

	printk(BIOS_DEBUG, "In vortex86mx_sb_enable %04x %04x.\n", vendor, model);

	/* If this is not the southbridge itself just return.
	 */

	if( (vendor != PCI_VENDOR_ID_DMP) || (model != PCI_DEVICE_ID_VORTEX86MX_SB))
		return;

	printk(BIOS_DEBUG, "Initialising Devices\n");

	pci_write_config8(dev, SB_REG_INTUART_CTRL, 0);
	c = pci_read_config8(dev, SB_REG_LADR);
	c |= 0x10;
	pci_write_config8(dev, SB_REG_LADR, c);

	/* Undocumented register */
	c = pci_read_config8(dev, SB_REG_BSCR);
	c |= 0xee;
	pci_write_config8(dev, SB_REG_BSCR, c);
	c = pci_read_config8(dev, SB_REG_BSCR + 1);
	c |= 0x4e;
	pci_write_config8(dev, SB_REG_BSCR + 1, c);
	
	/* SB Internal Peripheral Feature Control Register:
	[24-25] Set 4 clock for ISA 8bits I/O cycle wait-state */
	c = pci_read_config8(dev, 0xc3);
	c |= 0x3;
	pci_write_config8(dev, 0xc3, c);

	/* SB Internal Peripheral Feature Control Register:
	[16]  Enable read/write internal IO zero  wait state
	[18-19] Set 4 clock for ISA 8bits Memory cycle wait-state
	[21] Set 1 clock for ISA 16bits Memory cycle wait-state */
	c = pci_read_config8(dev, 0xc2);
	c |= 0x2d;
	pci_write_config8(dev, 0xc2, c);

	c = pci_read_config8(dev, SB_REG_SERIRQ_CTRL);
	c |= 0xd2;
	pci_write_config8(dev, SB_REG_SERIRQ_CTRL, c);

	/* Enable LPC function, enable Serial IRQ mode repetition */
	c = pci_read_config8(dev, SB_REG_LPC_CTRL);
	c &= ~0xf8;
	c |= 0x5;
	pci_write_config8(dev, SB_REG_LPC_CTRL, c);
	c = pci_read_config8(dev, SB_REG_INUART_CTRL);
	c |= 0xa0;
	pci_write_config8(dev, SB_REG_INUART_CTRL, c);
	
	/* SMM Base Address Control Register */
	c = pci_read_config8(dev, SB_REG_SMM_BAR);
	c |= 0x16;
	pci_write_config8(dev, SB_REG_SMM_BAR, c);
	c = pci_read_config8(dev, SB_REG_SMM_BAR + 1);
	c |= 0xff;
	pci_write_config8(dev, SB_REG_SMM_BAR + 1, c);

	/* make sure interupt controller is configured before keyboard init */
	setup_i8259();

	/* enable RTC and ethernet */
	regval = pci_read_config8(dev, 0x51);
	regval |= 0x18;
	pci_write_config8(dev, 0x51, regval);

	/* enable USB 1.1 & USB 2.0 - redundant really since we've
	 * already been there - see note above
	 */
	// USB Init

	/* turn on keyboard */
	keyboard_on(dev);
}

struct chip_operations southbridge_dmp_vortex86mx_ops = {
	CHIP_NAME("DMP Vortex86MX Southbridge")
	.enable_dev = vortex86mx_sb_enable,
};
