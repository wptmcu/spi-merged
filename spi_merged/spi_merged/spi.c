/*
 * spi.c
 *
 * Created: 2023-07-31 오후 3:54:54
 *  Author: WARP000046N
 */ 
#define F_CPU (4000000UL)
#include <avr/io.h>


void SPI_init()
{
// 	PORTA.DIR |=    0b11111111;
// 	PORTA.OUT |=	0b00000000;
// 	SPI0.CTRLA |=	SPI_MASTER_bm|SPI_ENABLE_bm;
// 	SPI0.CTRLB |=	0b10000010;	
// 	SPI0.INTCTRL |=	0b10000001;
// 	SPI0.INTFLAGS |= 0x00;
	
	
	PORTA.DIRSET |= PIN5_bm|PIN6_bm|PIN7_bm;
	PORTA.OUTSET |= PIN7_bm;
	SPI0.CTRLA |=	SPI_MASTER_bm|SPI_ENABLE_bm;
	SPI0.CTRLB |=	0b10000010;
	SPI0.INTCTRL |=	0b10000001;
	SPI0.INTFLAGS |= 0x00;
}

uint8_t SPI0_GetRxData()
{
	while (!(SPI0.INTFLAGS & SPI_RXCIF_bm))
	;
	return SPI0.DATA;
}