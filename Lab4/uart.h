/*
 * uart.h
 *
 *  Created on: Feb 21, 2019
 *      Author: axelzum
 */

#ifndef UART_H_
#define UART_H_

#include <stdint.h>
#include <inc/tm4c123gh6pm.h>
#include <stdbool.h>
#include "driverlib/interrupt.h"


void uart_init(void);

void uart_sendChar(char data);

char uart_receive(void);

void init_uart_interrupts();

void UART1_handler();


#endif /* UART_H_ */
