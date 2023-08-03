/*
 * uart.h
 *
 * Created: 2023-07-28 오후 4:38:55
 *  Author: WARP000046N
 */ 


#ifndef UART_H_
#define UART_H_

//CPU speed
#define F_CPU (4000000UL)
//bps
#define USART4_BAUD_RATE(BAUD_RATE) ((float)(F_CPU*64/(16 *(float)BAUD_RATE)) + 0.5)

#define uart_receive_buf_size 256
unsigned char uart_read_length;
unsigned char uart_receive_buf[uart_receive_buf_size];
unsigned char uart_read_data[uart_receive_buf_size];

/* Initialize UART4 interface
* If module is configured to disabled state, the clock to the UART is disabled
* Device's internal clock is in use
*/
void UART_init(void);

/*
* Write one character to UART4
* Function will block until a character can be accepted.
* After checking the DREIF setting, send character data
*/
void UART_sendChar(char c);

/*
* Assign array based on string length and send UART data to PC
*/
void UART_sendString(char *str);

/*
* UART Rx string check
*/
void uart_com_routine(char* u_com, char* read_val);

/*
* If you have data to read in Rx buf, you can read the characters.
*/
uint8_t UART_rx_get_c();

#endif /* UART_H_ */