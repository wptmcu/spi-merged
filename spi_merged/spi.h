/*
 * spi.h
 *
 * Created: 2023-07-31 오후 3:55:03
 *  Author: WARP000046N
 */ 


#ifndef SPI_H_
#define SPI_H_

void SPI_init(void);
uint8_t SPI0_SendTxData(uint8_t data);
void readADC(void);

#endif /* SPI_H_ */