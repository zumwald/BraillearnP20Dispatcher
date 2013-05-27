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
void DisplayInit(void){

	/*	Initialize GPIOs	*/
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);
#ifndef DEBUG
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOC);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOG);
#endif

	/*	Initialize GPIO drive modes	*/
	GPIOPinTypeGPIOOutputOD(GPIO_PORTB_BASE,GPIO_ALL);
#ifndef DEBUG
	GPIOPinTypeGPIOOutputOD(GPIO_PORTA_BASE,GPIO_ALL);
	GPIOPinTypeGPIOOutputOD(GPIO_PORTC_BASE,GPIO_HNIB);
	GPIOPinTypeGPIOOutputOD(GPIO_PORTD_BASE,GPIO_LNIB);
	GPIOPinTypeGPIOOutputOD(GPIO_PORTE_BASE,GPIO_LNIB);
	GPIOPinTypeGPIOOutputOD(GPIO_PORTG_BASE,GPIO_LNIB);
#endif
}

/********************************************************************
* DisplayTask() - The main P20 display task, addresses 4 cells
********************************************************************/
void DisplayTask(void){

#if defined(DB_DISPLAY) && defined(DB_PORT)
	GPIOPinWrite(DB_PORT, DB_DISPLAY, 0);
#endif
	UARTGetBuffer((INT8U *)&buffer);
	if (buffer[0]){
		GPIOPinWrite(GPIO_PORTB_BASE,GPIO_ALL,~buffer[0]);
	}else{
		/*	No Update to display	*/
		//GPIOPinWrite(GPIO_PORTB_BASE,GPIO_ALL,buffer[0]);
		//GPIOPinWrite(GPIO_PORTB_BASE,GPIO_ALL,~buffer[0]);
	}
#if defined(DB_DISPLAY) && defined(DB_PORT)
	GPIOPinWrite(DB_PORT, DB_DISPLAY, DB_DISPLAY);
#endif
}
