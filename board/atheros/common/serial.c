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

#include <asm/addrspace.h>
#include <asm/types.h>
#include <config.h>
#include <atheros.h>

int serial_init(void)
{
//#if !defined(CONFIG_ATH_EMULATION)
	uint32_t div, val;

	div = ath_uart_freq() / (16 * CONFIG_BAUDRATE);
#if defined(CONFIG_SCO_SLAVE_CONNECTED)
	val = ath_reg_rd(GPIO_OE_ADDRESS) & (~0xcbf410u);
#elif defined(CONFIG_MACH_QCA956x)
	val = ath_reg_rd(GPIO_OE_ADDRESS) & 0xbbfdf6;
#else
	val = ath_reg_rd(GPIO_OE_ADDRESS) & (~0xcffc10u);
#endif
	ath_reg_wr(GPIO_OE_ADDRESS, val);

#ifdef CONFIG_MACH_QCA956x

#if defined(UART_RX20_TX22)

	val = (ath_reg_rd(GPIO_OE_ADDRESS) & (~0x400000));
	ath_reg_wr(GPIO_OE_ADDRESS, val);

	ath_reg_rmw_clear(GPIO_OUT_FUNCTION5_ADDRESS,
			GPIO_OUT_FUNCTION5_ENABLE_GPIO_22_MASK);

	ath_reg_rmw_set(GPIO_OUT_FUNCTION5_ADDRESS,
			GPIO_OUT_FUNCTION5_ENABLE_GPIO_22_SET(0x16));

	ath_reg_rmw_clear(GPIO_IN_ENABLE0_ADDRESS,
			GPIO_IN_ENABLE0_UART_SIN_MASK);
   
	ath_reg_rmw_set(GPIO_IN_ENABLE0_ADDRESS,
			GPIO_IN_ENABLE0_UART_SIN_SET(0x14));
#elif defined(UART_RX18_TX22)
	val = (ath_reg_rd(GPIO_OE_ADDRESS) & (~0x400000)) | 0x40000;
	ath_reg_wr(GPIO_OE_ADDRESS, val);

	ath_reg_rmw_clear(GPIO_OUT_FUNCTION5_ADDRESS,
			GPIO_OUT_FUNCTION5_ENABLE_GPIO_22_MASK);
	ath_reg_rmw_set(GPIO_OUT_FUNCTION5_ADDRESS,
			GPIO_OUT_FUNCTION5_ENABLE_GPIO_22_SET(0x16));
	ath_reg_rmw_clear(GPIO_IN_ENABLE0_ADDRESS,
			GPIO_IN_ENABLE0_UART_SIN_MASK);
  
	ath_reg_rmw_set(GPIO_IN_ENABLE0_ADDRESS,
			GPIO_IN_ENABLE0_UART_SIN_SET(0x12));

#elif defined(UART_RX18_TX20)
	val = (ath_reg_rd(GPIO_OE_ADDRESS) & (~0x100000)) | 0x40000;
	ath_reg_wr(GPIO_OE_ADDRESS, val);

	val = ath_reg_rd(GPIO_OUT_ADDRESS) | 0xeffff6;
	ath_reg_wr(GPIO_OUT_ADDRESS, val);

	ath_reg_rmw_clear(GPIO_OUT_FUNCTION5_ADDRESS,
			GPIO_OUT_FUNCTION5_ENABLE_GPIO_20_MASK);
	ath_reg_rmw_set(GPIO_OUT_FUNCTION5_ADDRESS,
			GPIO_OUT_FUNCTION5_ENABLE_GPIO_20_SET(0x16));
	ath_reg_rmw_clear(GPIO_IN_ENABLE0_ADDRESS,
			GPIO_IN_ENABLE0_UART_SIN_MASK);
  
	ath_reg_rmw_set(GPIO_IN_ENABLE0_ADDRESS,
			GPIO_IN_ENABLE0_UART_SIN_SET(0x12));

#elif defined(UART_RX24_TX20)
	// Turn off LED before XLNA swap to GPO
	val = ath_reg_rd(GPIO_OUT_ADDRESS) | 0xaffff6;
	ath_reg_wr(GPIO_OUT_ADDRESS, val);
	//Switch GPI and GPO and XPA, XLNA
	ath_reg_wr(GPIO_FUNCTION_ADDRESS, 0x8000);

	val = (ath_reg_rd(GPIO_OE_ADDRESS) & (~0x100000)) | 0x1000000;
	ath_reg_wr(GPIO_OE_ADDRESS, val);

	ath_reg_rmw_set(GPIO_OUT_FUNCTION5_ADDRESS,
			GPIO_OUT_FUNCTION5_ENABLE_GPIO_20_SET(0x16));
	ath_reg_rmw_clear(GPIO_IN_ENABLE0_ADDRESS,
			GPIO_IN_ENABLE0_UART_SIN_SET(0xff));

	ath_reg_rmw_set(GPIO_IN_ENABLE0_ADDRESS,
			GPIO_IN_ENABLE0_UART_SIN_SET(0x18));
  
#elif defined(TEST_BOARD_UART)
	//Switch GPI and GPO and XPA1, ANTC
	ath_reg_wr(GPIO_FUNCTION_ADDRESS, 0xc000);

	val = ath_reg_rd(GPIO_OE_ADDRESS) & (~0x2000);
	ath_reg_wr(GPIO_OE_ADDRESS, val);

	ath_reg_rmw_clear(GPIO_OUT_FUNCTION3_ADDRESS,
			GPIO_OUT_FUNCTION3_ENABLE_GPIO_13_MASK);

	ath_reg_rmw_set(GPIO_OUT_FUNCTION3_ADDRESS,
			GPIO_OUT_FUNCTION3_ENABLE_GPIO_13_SET(0x16));
	
	ath_reg_rmw_clear(GPIO_IN_ENABLE0_ADDRESS,
			GPIO_IN_ENABLE0_UART_SIN_SET(0xff));

	ath_reg_rmw_set(GPIO_IN_ENABLE0_ADDRESS,
			GPIO_IN_ENABLE0_UART_SIN_SET(0x17));

#else
	val = (ath_reg_rd(GPIO_OE_ADDRESS) & (~0x100000)) | 0x80000;
	ath_reg_wr(GPIO_OE_ADDRESS, val);

	ath_reg_rmw_set(GPIO_OUT_FUNCTION5_ADDRESS,
			GPIO_OUT_FUNCTION5_ENABLE_GPIO_20_SET(0x16));
	ath_reg_rmw_clear(GPIO_IN_ENABLE0_ADDRESS,
			GPIO_IN_ENABLE0_UART_SIN_SET(0xff));

	ath_reg_rmw_set(GPIO_IN_ENABLE0_ADDRESS,
			GPIO_IN_ENABLE0_UART_SIN_SET(0x13));

#endif

	val = ath_reg_rd(GPIO_OUT_ADDRESS) | 0xaffff6;
	ath_reg_wr(GPIO_OUT_ADDRESS, val);

	val = ath_reg_rd(GPIO_SPARE_ADDRESS);
	ath_reg_wr(GPIO_SPARE_ADDRESS, (val | 0x8402));


#else
	ath_reg_rmw_set(GPIO_OUT_FUNCTION2_ADDRESS,
			GPIO_OUT_FUNCTION2_ENABLE_GPIO_10_SET(0x16));

	ath_reg_rmw_clear(GPIO_IN_ENABLE0_ADDRESS,
			GPIO_IN_ENABLE0_UART_SIN_SET(0xff));

	ath_reg_rmw_set(GPIO_IN_ENABLE0_ADDRESS,
			GPIO_IN_ENABLE0_UART_SIN_SET(0x9));

	val = ath_reg_rd(GPIO_OUT_ADDRESS) | 0xcffc10u;
	ath_reg_wr(GPIO_OUT_ADDRESS, val);

	val = ath_reg_rd(GPIO_SPARE_ADDRESS);
	ath_reg_wr(GPIO_SPARE_ADDRESS, (val | 0x8402));

	ath_reg_wr(GPIO_OUT_ADDRESS, 0x2f);
#endif
	/*
	 * set DIAB bit
	 */
	ath_uart_wr(OFS_LINE_CONTROL, 0x80);

	/* set divisor */
	ath_uart_wr(OFS_DIVISOR_LSB, (div & 0xff));
	ath_uart_wr(OFS_DIVISOR_MSB, ((div >> 8) & 0xff));

	/* clear DIAB bit*/
	ath_uart_wr(OFS_LINE_CONTROL, 0x00);

	/* set data format */
	ath_uart_wr(OFS_DATA_FORMAT, 0x3);

	ath_uart_wr(OFS_INTR_ENABLE, 0);
//#endif
	return 0;
}

int serial_tstc (void)
{
	return(ath_uart_rd(OFS_LINE_STATUS) & 0x1);
}

u8 serial_getc(void)
{
	while(!serial_tstc());

	return ath_uart_rd(OFS_RCV_BUFFER);
}


void serial_putc(u8 byte)
{
	if (byte == '\n') serial_putc ('\r');

	while (((ath_uart_rd(OFS_LINE_STATUS)) & 0x20) == 0x0);

	ath_uart_wr(OFS_SEND_BUFFER, byte);
}

void serial_setbrg (void)
{
}

void serial_puts (const char *s)
{
	while (*s)
	{
		serial_putc (*s++);
	}
}
