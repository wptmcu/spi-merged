/*
 * spi.c
 *
 * Created: 2023-07-31 오후 3:54:54
 *  Author: WARP000046N
 */ 
#define F_CPU (4000000UL)
#include <avr/io.h>
#include <util/delay.h>
#include "uart.h"
#include <avr/interrupt.h>

uint8_t result;
uint8_t byte_first;
uint8_t byte_second;

uint8_t firstMask = 0b11110000;
uint8_t secondMask = 0b00001111;

void SPI_init()
{
	PORTA.DIR |= PIN4_bm;
	PORTA.DIR &= ~PIN5_bm;
	PORTA.DIR |= PIN6_bm;
	PORTA.DIR |= PIN7_bm;
	SPI0.CTRLA |= SPI_MASTER_bm | SPI_ENABLE_bm;
	SPI0.CTRLB |= SPI_BUFEN_bm | SPI_MODE1_bm;
	SPI0.INTCTRL |= SPI_RXCIE_bm | SPI_IE_bm;
	SPI0.CTRLA &= ~SPI_DORD_bm;
}

inline static uint8_t SPI0_SendTxData(uint8_t data)
{
	SPI0.DATA = data;
	
	//asm volatile("nop");	
	while (!(SPI0.INTFLAGS & SPI_IF_bm));
	
	return SPI0.DATA;
}

void readADC(void)
{
	PORTA.OUTCLR = PIN7_bm;
	byte_first = SPI0_SendTxData(0x00);
	byte_second = SPI0_SendTxData(0x00);
	PORTA.OUTSET = PIN7_bm;
	byte_first &= firstMask; //Limits the value of the byte
	byte_second &= secondMask; //Limits the value of the byte
	uint8_t digitalValue = ((byte_second << 8) | byte_first) >> 4;
	//float value = ((float)digitalValue * 5) / 256; //The digital value is converted to an analogue voltage using a VREF of 5V
	UART_sendChar(digitalValue);
	//return value;
}