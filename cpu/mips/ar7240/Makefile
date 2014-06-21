#
# Copyright (c) 2013 Qualcomm Atheros, Inc.
#
# See file CREDITS for list of people who contributed to this
# project.
#
# This program is free software; you can redistribute it and/or
# modify it under the terms of the GNU General Public License as
# published by the Free Software Foundation; either version 2 of
# the License, or (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program; if not, write to the Free Software
# Foundation, Inc., 59 Temple Place, Suite 330, Boston,
# MA 02111-1307 USA
#

include $(TOPDIR)/config.mk

LIB	= lib$(SOC).a

START	=
#OBJS	= ar7240_serial.o ag7240.o ar7240_flash.o meminit.o

OBJS	= meminit.o 

ifeq ($(BOARD), ap121)
OBJS	+= hornet_serial.o
SOBJS	+= hornet_ddr_init.o
else
OBJS	+= ar7240_serial.o
endif

ifneq ($(BUILD_EMU), )
OBJS    += hornet_ag7240.o
else
ifneq ($(findstring db12x,$(BOARD)),)
OBJS    += ag934x.o
else
ifneq ($(findstring reh132,$(BOARD)),)
OBJS    += ag934x.o
else
ifneq ($(findstring dhp,$(BOARD)),)
OBJS    += ag934x.o
else
ifneq ($(findstring aph,$(BOARD)),)
OBJS    += ag934x.o
else
ifneq ($(findstring ap123,$(BOARD)),)
OBJS    += ag934x.o
else
ifneq ($(findstring ap120,$(BOARD)),)
OBJS    += ag934x.o
else
OBJS    += ag7240.o
endif
endif
endif
endif
endif
endif
endif

SOBJS	+= 

all:	.depend $(START) $(LIB)

$(LIB):	$(OBJS) $(SOBJS) $(OBJS-0)
	$(AR) crv $@ $(OBJS) $(SOBJS)

#########################################################################

.depend:	Makefile $(START:.o=.S) $(OBJS:.o=.c)
		$(CC) -M $(CFLAGS) $(START:.o=.S) $(OBJS:.o=.c) > $@

sinclude .depend

#########################################################################
