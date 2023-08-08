/*
 * uart.c
 *
 * Created: 2023-07-28 오후 4:38:45
 *  Author: WARP000046N
 */

#define F_CPU (4000000UL)
#define USART4_BAUD_RATE(BAUD_RATE) ((float)(F_CPU*64/(16 *(float)BAUD_RATE)) + 0.5)

#include <avr/io.h>
#include <util/delay.h>
#include <string.h>

#include "uart.h"

#define uart_receive_buf_size 256
unsigned char uart_read_length = 0;
unsigned char uart_receive_buf[uart_receive_buf_size];
unsigned char uart_read_data[uart_receive_buf_size];

void UART_init(void)
{
	PORTE.DIR &= ~PIN1_bm;
	PORTE.DIR |= PIN0_bm;
	//UART register
	USART4.BAUD = (uint16_t)USART4_BAUD_RATE(9600);
	USART4.CTRLA |= USART_RXCIE_bm;
	USART4.CTRLB |= USART_TXEN_bm | USART_RXEN_bm;
	USART4.CTRLC |= USART_CHSIZE1_bm | USART_CHSIZE0_bm;
}

void UART_sendChar(unsigned char c)
{
	while (!(USART4.STATUS & USART_DREIF_bm))
	{
		;
	}
	USART4.TXDATAL = c;
}


void UART_sendString(char *str)
{
	for(size_t i = 0; i < strlen(str); i++)
	{
		UART_sendChar(str[i]);
	}
}

uint8_t UART_rx_get_c()
{
	while(!(USART4.STATUS & USART_RXCIF_bm))
	;
	return USART4.RXDATAL;
}

void uart_com_routine(char* u_com, char* read_val)
{
	if(!strcmp(u_com, "uart"))
	{
		UART_sendString("uart4 serial\r\n");
	}
}