
#include <arch/pirq_routing.h>

const struct irq_routing_table intel_irq_routing_table = {
	PIRQ_SIGNATURE,				/* u32 signature */
	PIRQ_VERSION,				/* u16 version   */
	32 + 14 * CONFIG_IRQ_SLOT_COUNT,	/* Max. number of devices on the bus */
	0x00,					/* Where the interrupt router lies (bus) */
	(0x0 << 3) | 0x0,			/* Where the interrupt router lies (dev) */
	0xca0,					/* IRQs devoted exclusively to PCI usage */
	0x17f3,					/* Vendor */
	0x6021,					/* Device */
	0,					/* Miniport */
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},	/* u8 rfu[11] */
	0x00,					/* Checksum */
	{
	/*-------------------+---------------------------+---------------------------+---------------------------+---------------------------+-------------------*/
	/* Device Location   |        Int A Pin          |        Int B Pin          |        Int C Pin          |        Int D Pin          |                   */
	/*-------------------+---------------------------+---------------------------+---------------------------+---------------------------+-------------------*/
	/* PCI Bus  Dev Num  | Chipset   Bitmap of IRQs  | Chipset   Bitmap of IRQs  | Chipset   Bitmap of IRQs  | Chipset   Bitmap of IRQs  | Physical  Reserved*/
	/* Number   (Shl 3)  | Reg       Routable to Pin | Reg       Routable Pin    | Reg       Routable Pin    | Reg       Routable Pin    | Slot Num  Byte    */
	/*-------------------+---------------------------+---------------------------+---------------------------+---------------------------+-------------------*/
	{0x00,       0x08,    {{0x001,          0xDEF8},  {0x002,          0xDEF8},   {0x003,          0xDEF8},   {0x004,          0xDEF8}},        0x1, 0x0},
	{0x00,       0x10,    {{0x002,          0xDEF8},  {0x003,          0xDEF8},   {0x004,          0xDEF8},   {0x001,          0xDEF8}},        0x2, 0x0},
	{0x00,       0x18,    {{0x003,          0xDEF8},  {0x004,          0xDEF8},   {0x001,          0xDEF8},   {0x002,          0xDEF8}},        0x3, 0x0},
	{0x00,       0x20,    {{0x004,          0xDEF8},  {0x001,          0xDEF8},   {0x002,          0xDEF8},   {0x003,          0xDEF8}},        0x4, 0x0},
	{0x00,       0x28,    {{0x001,          0xDEF8},  {0x002,          0xDEF8},   {0x003,          0xDEF8},   {0x004,          0xDEF8}},        0x5, 0x0},
	{0x00,       0x30,    {{0x002,          0xDEF8},  {0x003,          0xDEF8},   {0x004,          0xDEF8},   {0x001,          0xDEF8}},        0x6, 0x0},
	{0x00,       0x68,    {{0x00F,          0xDEF8},  {0x000,          0x0000},   {0x000,          0x0000},   {0x000,          0x0000}},        0x0, 0x0},
	{0x00,       0x40,    {{0x005,          0xDEF8},  {0x000,          0x0000},   {0x000,          0x0000},   {0x000,          0x0000}},        0x0, 0x0},
	{0x00,       0x50,    {{0x007,          0xDEF8},  {0x008,          0xDEF8},   {0x000,          0x0000},   {0x000,          0x0000}},        0x0, 0x0},
	{0x00,       0x58,    {{0x009,          0xDEF8},  {0x00A,          0xDEF8},   {0x000,          0x0000},   {0x000,          0x0000}},        0x0, 0x0},
	{0x00,       0x60,    {{0x00B,          0xDEF8},  {0x000,          0x0000},   {0x000,          0x0000},   {0x000,          0x0000}},        0x0, 0x0},
	}
};

inline unsigned long write_pirq_routing_table(unsigned long addr)
{
	return copy_pirq_routing_table(addr);
}
