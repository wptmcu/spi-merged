/*
 * spi.c
 *
 * Created: 2023-07-31 ¿ÀÈÄ 3:54:54
 *  Author: WARP000046N
 */ 
#define F_CPU (4000000UL)
#include <avr/io.h>


void SPI_init()
{
	PORTA.DIR = 0xD0;
	SPI0.CTRLA = 0b00100001;
	SPI0.CTRLB = 0b10000000;	
	SPI0.INTCTRL = 0b10000001;
	SPI0.INTFLAGS = 0x00;
}

uint8_t SPI0_GetRxData()
{
	while (!(SPI0.INTFLAGS & SPI_RXCIF_bm))
	;
	return SPI0.DATA;
}