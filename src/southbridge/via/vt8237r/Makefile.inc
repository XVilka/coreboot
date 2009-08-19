##
## This file is part of the coreboot project.
##
## Copyright (C) 2007, 2009 Rudolf Marek <r.marek@assembler.cz>
##
## This program is free software; you can redistribute it and/or modify
## it under the terms of the GNU General Public License v2 as published by
## the Free Software Foundation.
##
## This program is distributed in the hope that it will be useful,
## but WITHOUT ANY WARRANTY; without even the implied warranty of
## MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
## GNU General Public License for more details.
##
## You should have received a copy of the GNU General Public License
## along with this program; if not, write to the Free Software
## Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301 USA
##

driver-y +=  vt8237r.o
driver-y +=  vt8237_ctrl.o
driver-y +=  vt8237r_ide.o
driver-y +=  vt8237r_lpc.o
driver-y +=  vt8237r_sata.o
driver-y +=  vt8237r_usb.o
driver-y +=  vt8237r_nic.o
obj-$(CONFIG_HAVE_ACPI_TABLES) += vt8237_fadt.o