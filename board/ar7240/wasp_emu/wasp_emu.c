/*
 * Copyright (c) 2013 Qualcomm Atheros, Inc.
 *
 * See file CREDITS for list of people who contributed to this
 * project.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 * MA 02111-1307 USA
 */

#include <common.h>
#include <command.h>
#include <asm/mipsregs.h>
#include <asm/addrspace.h>
#include <config.h>
#include <version.h>
#include "ar7240_soc.h"

extern void ar7240_ddr_initial_config(uint32_t refresh);
extern int ar7240_ddr_find_size(void);

void
ar7240_usb_initial_config(void)
{
	ar7240_reg_wr_nf(AR7240_USB_PLL_CONFIG, 0x0a04081e);
	ar7240_reg_wr_nf(AR7240_USB_PLL_CONFIG, 0x0804081e);
}

void ar7240_gpio_config()
{
	/* Disable clock obs */
	ar7240_reg_wr (AR7240_GPIO_FUNC, (ar7240_reg_rd(AR7240_GPIO_FUNC) & 0xffe7e0ff));
	/* Enable eth Switch LEDs */
	ar7240_reg_wr (AR7240_GPIO_FUNC, (ar7240_reg_rd(AR7240_GPIO_FUNC) | 0xfa));
}

int
ar7240_mem_config(void)
{
#if !defined(CONFIG_WASP_EMU)
    unsigned int tap_val1, tap_val2;
    ar7240_ddr_initial_config(CFG_DDR_REFRESH_VAL);

    /* Default tap values for starting the tap_init*/
    if (!(is_ar7241() || is_ar7242()))  {
        ar7240_reg_wr (AR7240_DDR_TAP_CONTROL0, 0x8);
        ar7240_reg_wr (AR7240_DDR_TAP_CONTROL1, 0x9);
        ar7240_ddr_tap_init();
    }
    else {
        ar7240_reg_wr (AR7240_DDR_TAP_CONTROL0, 0x2);
        ar7240_reg_wr (AR7240_DDR_TAP_CONTROL1, 0x2);
        ar7240_reg_wr (AR7240_DDR_TAP_CONTROL2, 0x0);
        ar7240_reg_wr (AR7240_DDR_TAP_CONTROL3, 0x0);
    }

    tap_val1 = ar7240_reg_rd(0xb800001c);
    tap_val2 = ar7240_reg_rd(0xb8000020);

    printf("#### TAP VALUE 1 = 0x%x, 2 = 0x%x [0x%x: 0x%x]\n",
                tap_val1, tap_val2, *(unsigned *)0x80500000,
                *(unsigned *)0x80500004); 
    ar7240_usb_initial_config();
    ar7240_gpio_config();

#endif 
    return (ar7240_ddr_find_size());
}

long int initdram(int board_type)
{
	return (ar7240_mem_config());
}

int checkboard (void)
{
	printf("Wasp Emulation U-boot\n");
	return 0;
}
