/*
 * This file is part of the coreboot project.
 *
 * Copyright (C) 2007-2008 coresystems GmbH
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; version 2 of the License.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA
 */

#include <arch/pirq_routing.h>

const struct irq_routing_table intel_irq_routing_table = {
        PIRQ_SIGNATURE,         /* u32 signature */
        PIRQ_VERSION,           /* u16 version */
        32+16*CONFIG_IRQ_SLOT_COUNT,     /* Max. number of devices on the bus */
        0x00,                   /* Interrupt router bus */
        (0x1f << 3) | 0x0,      /* Interrupt router dev */
        0,                      /* IRQs devoted exclusively to PCI usage */
        0x8086,                 /* Vendor */
        0x8119,                 /* Device*/
	0,                      /* Miniport */
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, /* u8 rfu[11] */
        0xdf,                   /* Checksum (has to be set to some value that
                                 * would give 0 after the sum of all bytes
                                 * for this structure (including checksum).
                                 */
        {
                /* bus,        dev | fn,   {link, bitmap}, {link, bitmap}, {link, bitmap}, {link, bitmap}, slot, rfu */
                {0x00, (0x02 << 3) | 0x0, {{0x60, 0x5cb8}, {0x00, 0x0000}, {0x00, 0x0000}, {0x00, 0x0000}}, 0x0, 0x0},
                {0x00, (0x1e << 3) | 0x0, {{0x60, 0x5cb8}, {0x61, 0x5cb8}, {0x62, 0x5cb8}, {0x00, 0x0000}}, 0x0, 0x0},
                {0x00, (0x1f << 3) | 0x0, {{0x62, 0x5cb8}, {0x00, 0x0000}, {0x00, 0x0000}, {0x00, 0x0000}}, 0x0, 0x0},
                {0x00, (0x1a << 3) | 0x0, {{0x60, 0x5cb8}, {0x00, 0x0000}, {0x00, 0x0000}, {0x00, 0x0000}}, 0x0, 0x0},
                {0x00, (0x1d << 3) | 0x0, {{0x64, 0x8200}, {0x65, 0x8200}, {0x66, 0x8200}, {0x67, 0x8200}}, 0x0, 0x0},
                {0x00, (0x1b << 3) | 0x0, {{0x60, 0x5cb8}, {0x00, 0x0000}, {0x00, 0x0000}, {0x00, 0x0000}}, 0x0, 0x0},
                {0x00, (0x1c << 3) | 0x0, {{0x60, 0x5cb8}, {0x61, 0x5cb8}, {0x00, 0x0000}, {0x00, 0x0000}}, 0x0, 0x0},
                {0x01, (0x00 << 3) | 0x0, {{0x60, 0x5cb8}, {0x00, 0x0000}, {0x00, 0x0000}, {0x00, 0x0000}}, 0x0, 0x0},
                {0x02, (0x00 << 3) | 0x0, {{0x61, 0x5cb8}, {0x62, 0x5cb8}, {0x63, 0x5cb8}, {0x60, 0x5cb8}}, 0x2, 0x0},
                {0x00, (0x00 << 3) | 0x0, {{0x00, 0x0000}, {0x00, 0x0000}, {0x00, 0x0000}, {0x00, 0x0000}}, 0x0, 0x0},
        }
};

unsigned long write_pirq_routing_table(unsigned long addr)
{
        return copy_pirq_routing_table(addr);
}
