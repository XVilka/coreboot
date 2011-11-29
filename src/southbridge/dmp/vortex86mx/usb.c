#include <console/console.h>
#include <device/device.h>
#include <device/pci.h>
#include <device/pci_ops.h>
#include <device/pci_ids.h>

/* really nothing to do here, both usb 1.1 & 2.0 are normal PCI devices and so get resources allocated
   properly. They are part of the southbridge and are enabled in the chip enable function for the southbridge */

static void usb_init(struct device *dev)
{
	u8 c;

	printk(BIOS_DEBUG, "Configuring DMP Vortex86MX USB 2.0\n");

	c = pci_read_config8(dev, 0x0d);
	c |= 0x20;
	pci_write_config8(dev, 0x0d, c)
}

static struct device_operations usb_ops = {
	.read_resources   = pci_dev_read_resources,
	.set_resources    = pci_dev_set_resources,
	.enable_resources = pci_dev_enable_resources,
	.init             = usb_init,
	.enable           = 0,
	.ops_pci          = 0,
};

static const struct pci_driver northbridge_driver __pci_driver = {
	.ops    = &usb_ops,
	.vendor = PCI_VENDOR_ID_DMP,
	.device = PCI_DEVICE_ID_VORTEX86MX_USB,
};

