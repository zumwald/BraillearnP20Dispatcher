/*
 * Display.c
 *
 *  Created on: May 26, 2013
 *      Author: zumwald
 */
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
void DisplayInit();
void DisplayTask();

/********************************************************************
 * Private Resources
 ********************************************************************/
static INT8U buffer[BUFLEN];

/********************************************************************
 * DisplayInit() - Initialization routine for the Display module.
 ********************************************************************/
void DisplayInit(void) {

	/*	Initialize GPIOs	*/
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);
#ifndef DEBUG
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOC);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
#endif

	/*	Initialize GPIO drive modes	*/
	GPIOPinTypeGPIOOutputOD(GPIO_PORTB_BASE, GPIO_ALL);
#ifndef DEBUG
	GPIOPinTypeGPIOOutputOD(GPIO_PORTA_BASE, GPIO_ALL & ~(BIT0 | BIT1));
	GPIOPinTypeGPIOOutputOD(GPIO_PORTC_BASE, GPIO_HNIB);
	GPIOPinTypeGPIOOutputOD(GPIO_PORTD_BASE, GPIO_LNIB);
	GPIOPinTypeGPIOOutputOD(GPIO_PORTE_BASE, GPIO_ALL & ~(BIT6 | BIT7));
	GPIOPinTypeGPIOOutputOD(GPIO_PORTF_BASE, GPIO_LNIB);
#endif

	/*	Initialize States	*/
	GPIOPinWrite(GPIO_PORTB_BASE, GPIO_ALL, GPIO_ALL);
#ifndef DEBUG
	GPIOPinWrite(GPIO_PORTE_BASE, BIT4 | BIT5, GPIO_ALL);
	GPIOPinWrite(GPIO_PORTA_BASE, GPIO_ALL & ~(BIT0 | BIT1), GPIO_ALL);

	GPIOPinWrite(GPIO_PORTD_BASE, GPIO_LNIB, GPIO_ALL);
	GPIOPinWrite(GPIO_PORTC_BASE, GPIO_HNIB, GPIO_ALL);

	GPIOPinWrite(GPIO_PORTE_BASE, GPIO_LNIB, GPIO_ALL);
	GPIOPinWrite(GPIO_PORTF_BASE, GPIO_LNIB, GPIO_ALL);
#endif
}

/********************************************************************
 * DisplayTask() - The main P20 display task, addresses 4 cells
 ********************************************************************/
void DisplayTask(void) {

	INT8U i;

#if defined(DB_DISPLAY) && defined(DB_PORT)
	GPIOPinWrite(DB_PORT, DB_DISPLAY, 0);
#endif
	UARTGetBuffer((INT8U *) &buffer);

	GPIOPinWrite(GPIO_PORTB_BASE, GPIO_ALL, buffer[0]);

	GPIOPinWrite(GPIO_PORTE_BASE, BIT4 | BIT5, buffer[1] << 3);
	GPIOPinWrite(GPIO_PORTA_BASE, GPIO_ALL & ~(BIT0 | BIT1), buffer[1]);

	GPIOPinWrite(GPIO_PORTD_BASE, GPIO_LNIB, buffer[2]);
	GPIOPinWrite(GPIO_PORTC_BASE, GPIO_HNIB, buffer[2]);

	GPIOPinWrite(GPIO_PORTE_BASE, GPIO_LNIB, buffer[3]);
	GPIOPinWrite(GPIO_PORTF_BASE, GPIO_LNIB, buffer[3]>>4);

#if defined(DB_DISPLAY) && defined(DB_PORT)
	GPIOPinWrite(DB_PORT, DB_DISPLAY, DB_DISPLAY);
#endif
}
