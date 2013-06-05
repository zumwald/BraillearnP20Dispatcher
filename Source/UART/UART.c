 /*
 * UART.c
 *	Modifed ~~ See Below.
 *  Created on: May 22, 2013
 *      Author: Dan Zumwalt
 */

//*****************************************************************************
//
// uart_echo.c - Example for reading data from and writing data to the UART in
//               an interrupt driven fashion.
//
// Copyright (c) 2012 Texas Instruments Incorporated.  All rights reserved.
// Software License Agreement
//
// Texas Instruments (TI) is supplying this software for use solely and
// exclusively on TI's microcontroller products. The software is owned by
// TI and/or its suppliers, and is protected under applicable copyright
// laws. You may not combine this software with "viral" open-source
// software in order to form a larger program.
//
// THIS SOFTWARE IS PROVIDED "AS IS" AND WITH ALL FAULTS.
// NO WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT
// NOT LIMITED TO, IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE. TI SHALL NOT, UNDER ANY
// CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL, OR CONSEQUENTIAL
// DAMAGES, FOR ANY REASON WHATSOEVER.
//
// This is part of revision 9453 of the EK-LM4F120XL Firmware Package.
//
//*****************************************************************************
/********************************************************************
 * Project master header file
 ********************************************************************/
#include "includes.h"

/********************************************************************
 * Module Defines
 ********************************************************************/

/********************************************************************
 * Public Resources
 ********************************************************************/
void UARTSend(const unsigned char *pucBuffer, unsigned long ulCount);
void UARTTask(void);

/********************************************************************
 * Private Resources
 ********************************************************************/
static INT8U RxBuffer[BUFLEN];
static INT8U SyncBuffer[BUFLEN + 1];
static INT8U indexR;
static INT8U bFlag = FALSE;
static INT8U TxBuffer[BUFLEN];
static INT8U indexT, fTxFull;

/********************************************************************
 * UARTGetBuffer() - returns 8Byte Rx buffer contents or null if empty.
 ********************************************************************/
void UARTGetBuffer(INT8U *outbuf) {

	INT8U *ptr = SyncBuffer;

	/*	initialize outbuf to null	*/
	*outbuf = 0x00;

	while (*ptr != 0x00) {
		*(outbuf++) = *(ptr++);
	}
	*outbuf = 0x00;
}

//*****************************************************************************
//
// The UART interrupt handler.
//
//*****************************************************************************
void UARTIntHandler(void) {
	unsigned long ulStatus;
	INT8U ch;

	// Get the interrupt status.
	ulStatus = ROM_UARTIntStatus (UART2_BASE, true);

	// Clear the asserted interrupts.
	ROM_UARTIntClear (UART2_BASE, ulStatus);

	// Loop while there are characters in the receive FIFO.
	while (ROM_UARTCharsAvail (UART2_BASE)) {
		// Read the next character from the UART and write it back to the UART.
		ch = ROM_UARTCharGetNonBlocking (UART2_BASE);
		ROM_UARTCharPutNonBlocking (UART2_BASE, ch);// echo
		RxBuffer[indexR++] = ch;
		if (indexR == BUFLEN) {
			indexR = 0;
		}else{}
		bFlag = TRUE;
	}
}

//*****************************************************************************
//
// Send a string to the UART.	-	Public, Non-blocking
//
//*****************************************************************************
void UARTSend(const INT8U *pucBuffer, INT32U ulCount) {
	//
	// Loop while there are more characters to send.
	//
#if defined(DB_UART) && defined(DB_PORT)
	GPIOPinWrite(DB_PORT, DB_UART, 0);
#endif
	while (ulCount--) {
		//
		// Write the next character to the UART.
		//
		ROM_UARTCharPutNonBlocking (UART2_BASE, *pucBuffer++);
	}
#if defined(DB_UART) && defined(DB_PORT)
	GPIOPinWrite(DB_PORT, DB_UART, DB_UART);
#endif
}

//*****************************************************************************
//
// Send a string to the UART.	-	Public, Non-blocking
//
//*****************************************************************************
void COMSend(const INT8U *pucBuffer, INT32U ulCount) {
	//
	// Loop while there are more characters to send.
	//
#if defined(DB_UART) && defined(DB_PORT)
	GPIOPinWrite(DB_PORT, DB_UART, 0);
#endif
	while (ulCount--) {
		//
		// Write the next character to the UART.
		//
		ROM_UARTCharPutNonBlocking (UART0_BASE, *pucBuffer++);
	}
#if defined(DB_UART) && defined(DB_PORT)
	GPIOPinWrite(DB_PORT, DB_UART, DB_UART);
#endif
}

/********************************************************************
 * UARTInit() - Initialization routine for the UART module.
 ********************************************************************/
void UARTInit(void) {
	//
	// Enable lazy stacking for interrupt handlers.  This allows floating-point
	// instructions to be used within interrupt handlers, but at the expense of
	// extra stack usage.
	//
	FPUEnable();
	FPULazyStackingEnable();

	// Enable the peripherals used by this example.
	SysCtlPeripheralEnable(SYSCTL_PERIPH_UART2);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);

	SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);

	// Set GPIO A0 and A1 as UART pins.
	GPIOPinConfigure(GPIO_PD6_U2RX);
	GPIOPinConfigure(GPIO_PD7_U2TX);
	GPIOPinTypeUART(GPIO_PORTD_BASE, GPIO_PIN_6 | GPIO_PIN_7);

	GPIOPinConfigure(GPIO_PA0_U0RX);
	GPIOPinConfigure(GPIO_PA1_U0TX);
	GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);

	//	Set UART Clock source as 16MHZ crystal
	UARTClockSourceSet(UART2_BASE, UART_CLOCK_PIOSC);

	UARTClockSourceSet(UART0_BASE, UART_CLOCK_PIOSC);

	// Configure the UART for 115,200, 8-N-1 operation.
	UARTConfigSetExpClk(UART2_BASE, CRYSTAL_16MHZ, (INT32U) BAUD,
			(UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE | UART_CONFIG_PAR_NONE));

	UARTConfigSetExpClk(UART0_BASE, CRYSTAL_16MHZ, (INT32U) BAUD,
			(UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE | UART_CONFIG_PAR_NONE));

	/*	Enable FIFOs	*/
	UARTFIFOEnable(UART2_BASE);
	UARTFIFOLevelSet(UART2_BASE, UART_FIFO_TX1_8, UART_FIFO_RX1_8);

	UARTFIFOEnable(UART0_BASE);
	UARTFIFOLevelSet(UART0_BASE, UART_FIFO_TX4_8, UART_FIFO_RX4_8);

	UARTEnable(UART2_BASE);

	UARTEnable(UART0_BASE);

	// Enable the UART interrupt.
	IntEnable(INT_UART2);
	UARTIntEnable(UART2_BASE, UART_INT_RX | UART_INT_RT);

	//IntEnable(INT_UART0);
	//UARTIntEnable(UART0_BASE, UART_INT_RX | UART_INT_RT);

	/*	Variable initialization 	*/
	SyncBuffer[0] = 0x00;
	indexR = 0;
	bFlag = FALSE;
	TxBuffer[0] = 0x00;
	indexT = 0;
	fTxFull = FALSE;
}

/********************************************************************
 * UARTTask() - Timeslice task for UART communication
 ********************************************************************/
void UARTTask(void) {

	INT8U j;

#if defined(DB_UART) && defined(DB_PORT)
	GPIOPinWrite(DB_PORT, DB_UART, 0);
#endif
	/*	if data available, parse it	*/
	if (bFlag) {
		/*	Disable interrupts to Mutex Rx buffer access	*/
		UARTIntDisable(UART2_BASE, UART_INT_RX | UART_INT_RT);

		for (j = 0; j < indexR; j++) {
			SyncBuffer[j] = RxBuffer[j];
		}
		/*	Add null terminator	*/
		SyncBuffer[j] = 0x00;

		/*	Re-enable interrupts before returning to kernel	*/
		UARTIntEnable(UART2_BASE, UART_INT_RX | UART_INT_RT);

		/*	Send contents of TxBuffer	*/
		UARTSend(TxBuffer,indexT);

		//TODO Add parsing logic for commands, data transfer, etc.
	} else {
	}
	indexR = 0;
#if defined(DB_UART) && defined(DB_PORT)
	GPIOPinWrite(DB_PORT, DB_UART, DB_UART);
#endif
}
