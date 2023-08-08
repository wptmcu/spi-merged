/*
 * uart_test.c
 *
 * Created: 2023-07-28 오후 5:40:55
 * Author : WARP000046N
 */ 

#define F_CPU (4000000UL)
#define USART4_BAUD_RATE(BAUD_RATE) ((float)(F_CPU*64/(16 *(float)BAUD_RATE)) + 0.5)

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdio.h>
#include <string.h>
#include "uart.h"
#include "spi.h"



int main(void)
{
	
	//Rx Mode
	PORTA.DIR |= PIN2_bm | PIN3_bm;
	PORTC.DIR |= PIN7_bm;
	PORTD.DIR |= PIN4_bm;
	
	PORTA.OUTCLR |= PIN2_bm;
	PORTA.OUTSET |= PIN3_bm;
	PORTC.OUTCLR |= PIN7_bm;
	PORTD.OUTCLR |= PIN4_bm;
	
	SPI_init();
	UART_init();
	UART_sendString("serial\r\n");
	sei();
	while (1)
	{
		//_delay_ms(100);
		readADC();
	}	
}

ISR(USART4_RXC_vect)
{
	char data = UART_rx_get_c();
	if(uart_read_length < uart_receive_buf_size)
	{
		uart_receive_buf[uart_read_length++] = data;
		if (data == '\0')
		{
			memcpy(uart_read_data, uart_receive_buf, uart_read_length);
			memset(uart_receive_buf,0,uart_read_length);
			uart_read_length = 0;
			
			char* read_com = strtok((char*)uart_read_data," ");
			char* read_val = strtok(NULL, " ");
			
			uart_com_routine(read_com, read_val);
		}
	}
}