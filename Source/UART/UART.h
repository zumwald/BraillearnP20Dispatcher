/*
 * UART.h
 *
 *  Created on: May 22, 2013
 *      Author: zumwald
 */

#ifndef UART_H_
#define UART_H_

//*****************************************************************************
// Send a string to the UART.	-	Public, Non-blocking
//*****************************************************************************
extern void UARTSend(const unsigned char *pucBuffer, unsigned long ulCount);

//*****************************************************************************
// The UART interrupt handler.	- local echo
//*****************************************************************************
void UARTIntHandler(void);

/********************************************************************
* UARTInit() - Initialization routine for the UART module.
********************************************************************/
void UARTInit(void);

/********************************************************************
* UARTGetBuffer() - returns 8Byte Rx buffer contents null terminated.
********************************************************************/
void UARTGetBuffer(INT8U *buffer);

//*****************************************************************************
// Send the welcome string to the UART.	-	Public, BLOCKING 30mS
//*****************************************************************************
void UART_Welcome(void);

#endif /* UART_H_ */
