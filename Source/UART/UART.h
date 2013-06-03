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
// Send a char to the UART.	-	Public, Non-blocking
//*****************************************************************************
extern void UARTSendChar(INT8U ch);


//*****************************************************************************
// Send a char to the PC Com port.	-	Public, non-blocking
//*****************************************************************************
extern void COMSend(const INT8U *pucBuffer, INT32U ulCount);

//*****************************************************************************
// The UART interrupt handler.	- local echo
//*****************************************************************************
extern void UARTIntHandler(void);

/********************************************************************
* UARTInit() - Initialization routine for the UART module.
********************************************************************/
extern void UARTInit(void);

/********************************************************************
* UARTGetBuffer() - returns 8Byte Rx buffer contents null terminated.
********************************************************************/
extern void UARTGetBuffer(INT8U *buffer);

//*****************************************************************************
// Send the welcome string to the UART.	-	Public, BLOCKING 30mS
//*****************************************************************************
extern void UART_Welcome(void);

/********************************************************************
* KeyTask() - The main UART send/receive task
********************************************************************/
extern void UARTTask(void);

#endif /* UART_H_ */
