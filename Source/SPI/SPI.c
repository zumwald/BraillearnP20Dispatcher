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
	SysCtlPeripheralEnable(SYSCTL_PERIPH_UART2);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);

	// Set GPIO A0 and A1 as UART pins.
	GPIOPinConfigure(GPIO_PD6_U2RX);
	GPIOPinConfigure(GPIO_PD7_U2TX);
	GPIOPinTypeUART(GPIO_PORTD_BASE, GPIO_PIN_6 | GPIO_PIN_7);

	//	Set UART Clock source as 16MHZ crystal
	UARTClockSourceSet(UART2_BASE, UART_CLOCK_PIOSC);

	// Configure the UART for 115,200, 8-N-1 operation.
	UARTConfigSetExpClk(UART2_BASE, CRYSTAL_16MHZ, (INT32U) BAUD,
			(UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE | UART_CONFIG_PAR_NONE));

	/*	Enable FIFOs	*/
	//UARTFIFOEnable(UART2_BASE);
	//UARTFIFOLevelSet(UART2_BASE, UART_FIFO_TX4_1, UART_FIFO_RX4_1);

	// Enable the UART interrupt.
	//IntEnable(UART2_BASE);
	//UARTIntEnable(UART2_BASE, UART_INT_RX | UART_INT_RT);
}

/********************************************************************
 * SPISendChar() - Sends char of data to specified address, returns
 * 				  TRUE if ack is received from slave, otherwise FALSE.
 ********************************************************************/
INT8U SPISendChar(INT8U data, INT8U addr) {
	INT16U timeout = 0;

	ROM_UARTCharPutNonBlocking (UART2_BASE, &data);

	/*	wait for Rx ack	*/
	while (!ROM_UARTCharsAvail (UART2_BASE)) {
		if (timeout >= 1000) {
			return FALSE;
		} else {
		}
	}
	if (data == ROM_UARTCharGetNonBlocking (UART0_BASE)) {
		return TRUE;
	} else {
		return FALSE;
	}
}
/*******************************************************************/
