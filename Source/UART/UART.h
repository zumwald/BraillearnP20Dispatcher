/*
 * UART.h
 *
 *  Created on: May 22, 2013
 *      Author: zumwald
 */

#ifndef UART_H_
#define UART_H_

extern void UARTSend(const unsigned char *pucBuffer, unsigned long ulCount);

void UARTIntHandler(void);

void UARTInit(void);

#endif /* UART_H_ */
