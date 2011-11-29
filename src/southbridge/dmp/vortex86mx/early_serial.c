/*
 * Enable the serial evices on the DMP Vortex86MX
 */


/* The base address is 0x15c, 0x2e, depending on config bytes */

#define SIO_BASE 0x3f0
#define SIO_DATA  SIO_BASE+1

static void vortex86mx_writepnpaddr(uint8_t val)
{
	outb(val, 0x2e);
	outb(val, 0xeb);
}

static void vortex86mx_writepnpdata(uint8_t val)
{
	outb(val, 0x2f);
	outb(val, 0xeb);
}


static void vortex86mx_writesiobyte(uint16_t reg, uint8_t val)
{
	outb(val, reg);
}

static void vortex86mx_writesioword(uint16_t reg, uint16_t val)
{
	outw(val, reg);
}


/* regs we use: 85, and the southbridge devfn is defined by the
   mainboard
 */

static void enable_vortex86mx_serial(void)
{
	// turn on pnp
	vortex86mx_writepnpaddr(0x87);
	vortex86mx_writepnpaddr(0x87);
	// now go ahead and set up com1.
	// set address
	vortex86mx_writepnpaddr(0x7);
	vortex86mx_writepnpdata(0x2);
	// enable serial out
	vortex86mx_writepnpaddr(0x30);
	vortex86mx_writepnpdata(0x1);
	// serial port 1 base address (FEh)
	vt8235_writepnpaddr(0x60);
	vt8235_writepnpdata(0xfe);
	// serial port 1 IRQ (04h)
	vt8235_writepnpaddr(0x70);
	vt8235_writepnpdata(0x4);
	// serial port 1 control
	vt8235_writepnpaddr(0xf0);
	vt8235_writepnpdata(0x2);
	// turn of pnp
	vortex86mx_writepnpaddr(0xaa);

	// set up reg to set baud rate.
	vortex86mx_writesiobyte(0x3fb, 0x80);
	// Set 115 kb
	vortex86mx_writesioword(0x3f8, 1);
	// Set 9.6 kb
	//	WRITESIOWORD(0x3f8, 12)
	// now set no parity, one stop, 8 bits
	vortex86mx_writesiobyte(0x3fb, 3);
	// now turn on RTS, DRT
	vortex86mx_writesiobyte(0x3fc, 3);
	// Enable interrupts
	vortex86mx_writesiobyte(0x3f9, 0xf);
	// should be done. Dump a char for fun.
	vortex86mx_writesiobyte(0x3f8, 48);
}
