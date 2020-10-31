/*
 * UART.h
 *
 *  Created on: Sep 12, 2019
 *      Author: Joseph Hanna
 */

#ifndef UART_H_
#define UART_H_

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
/* Set a certain bit in any register */
#define SET_BIT(REG,BIT) (REG|=(1<<BIT))

/* Clear a certain bit in any register */
#define CLEAR_BIT(REG,BIT) (REG&=(~(1<<BIT)))

/* Toggle a certain bit in any register */
#define TOGGLE_BIT(REG,BIT) (REG^=(1<<BIT))

/* Rotate right the register value with specific number of rotates */
#define ROR(REG,num) ( REG= (REG>>num) | (REG<<(8-num)) )

/* Rotate left the register value with specific number of rotates */
#define ROL(REG,num) ( REG= (REG<<num) | (REG>>(8-num)) )

/* Check if a specific bit is set in any register and return true if yes */
#define BIT_IS_SET(REG,BIT) ( REG & (1<<BIT) )

/* Check if a specific bit is cleared in any register and return true if yes */
#define BIT_IS_CLEAR(REG,BIT) ( !(REG & (1<<BIT)) )

/* UART Driver Baud Rate */
#define USART_BAUDRATE 9600

/************************** Functions Prototypes ***********************/
void uartInit_test();

void UART_init(void);

void UART_sendByte(const unsigned char data);

unsigned char UART_recieveByte(void);

void UART_sendString(const unsigned char *Str);

void UART_receiveString(unsigned char *Str); // Receive until #

#endif /* UART_H_ */
