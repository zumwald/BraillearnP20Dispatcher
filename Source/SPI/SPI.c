/*
 * SPI.c
 *
 *  Created on: May 22, 2013
 *      Author: zumwald
 **********************************************************************
 * Project master header file
 ********************************************************************/
#include "includes.h"

/********************************************************************
 * Module Defines
 ********************************************************************/
#define BAUD	9600

/********************************************************************
 * Public Resources
 ********************************************************************/
void SPIInit(void);
INT8U SPISendChar(INT8U data, INT8U addr);

/********************************************************************
 * Private Resources
 ********************************************************************/

/********************************************************************
 * SPIInit() - SPI Initialization. Must run before calling SPI funcs
 ********************************************************************/
void SPIInit(void) {
	//
	// Enable lazy stacking for interrupt handlers.  This allows floating-point
	// instructions to be used within interrupt handlers, but at the expense of
	// extra stack usage.
	//
	FPUEnable();
	FPULazyStackingEnable();

	// Enable the peripherals used by this example.
	SysCtlPeripheralEnable(SYSCTL_PERIPH_UART7);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);

	// Set GPIO A0 and A1 as UART pins.
	GPIOPinConfigure(GPIO_PE0_U7RX);
	GPIOPinConfigure(GPIO_PE1_U7TX);
	GPIOPinTypeUART(GPIO_PORTE_BASE, GPIO_PIN_0 | GPIO_PIN_1);

	//	Set UART Clock source as 16MHZ crystal
	UARTClockSourceSet(UART7_BASE, UART_CLOCK_PIOSC);

	// Configure the UART for 115,200, 8-N-1 operation.
	UARTConfigSetExpClk(UART7_BASE, CRYSTAL_16MHZ, (INT32U) BAUD,
			(UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE | UART_CONFIG_PAR_NONE));

	UARTEnable(UART7_BASE);

	/*	Enable FIFOs	*/
	//UARTFIFOEnable(UART7_BASE);
	//UARTFIFOLevelSet(UART7_BASE, UART_FIFO_TX1_8, UART_FIFO_RX1_8);

	// Enable the UART interrupt.
	//IntEnable(INT_UART7);
	//UARTIntEnable(UART7_BASE, UART_INT_RX | UART_INT_RT);
}

/********************************************************************
 * SPISendChar() - Sends char of data to specified address, returns
 * 				  TRUE if ack is received from slave, otherwise FALSE.
 ********************************************************************/
INT8U SPISendChar(INT8U data, INT8U addr) {
	INT16U timeout = 0;

	ROM_UARTCharPutNonBlocking (UART7_BASE, data);

	/*	wait for Rx ack	*/
	while (!ROM_UARTCharsAvail (UART7_BASE)) {
		if (timeout >= 1000) {
			return FALSE;
		} else {
			timeout++;
		}
	}
	if (data == ROM_UARTCharGetNonBlocking (UART7_BASE)) {
		return TRUE;
	} else {
		return FALSE;
	}
}
/*******************************************************************/

//*****************************************************************************
//
// The UART interrupt handler.
//
//*****************************************************************************
void SPIIntHandler(void) {
	unsigned long ulStatus;
	INT8U ch;

	// Get the interrupt status.
	ulStatus = ROM_UARTIntStatus (UART7_BASE, true);

	// Clear the asserted interrupts.
	ROM_UARTIntClear (UART7_BASE, ulStatus);

	// Loop while there are characters in the receive FIFO.
	while (ROM_UARTCharsAvail (UART7_BASE)) {
		// Read the next character from the UART and write it back to the UART.
		ch = ROM_UARTCharGetNonBlocking (UART7_BASE);
		ROM_UARTCharPutNonBlocking (UART7_BASE, ch);
	}
}
