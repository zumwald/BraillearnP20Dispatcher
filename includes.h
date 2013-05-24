/*************************************************************************
* includes.h - Master header file template for star12 projects.
*              This version is for ETec454 Lab1 using the Metrowerks 
*              compiler. 
*
* Todd Morton 01/05/05
* Modified 01/31/13 by Dan Zumwalt
**************************************************************************
* General type definitions 
*************************************************************************/
#ifndef _INCLUDES_H
#define _INCLUDES_H

typedef unsigned char   INT8U;
typedef signed char     INT8S;
typedef unsigned short  INT16U;
typedef signed short    INT16S;
typedef unsigned long   INT32U;
typedef signed long     INT32S;

/*************************************************************************
* General Defined Constants 
*************************************************************************/
#define FALSE    0
#define TRUE     1

/*************************************************************************
* General defined macros 
*************************************************************************/
#define FOREVER()       while(1)
#define TRAP()          while(1){}

/*************************************************************************
* MCU specific definitions
* Move the comment to use the project MCU, or enter a new MCU header.
*************************************************************************/
#include "inc/hw_ints.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/sysctl.h"
#include "driverlib/interrupt.h"
#include "driverlib/gpio.h"
#include "driverlib/timer.h"
#include "driverlib/debug.h"
#include "driverlib/fpu.h"
#include "driverlib/pin_map.h"
#include "driverlib/rom.h"
#include "driverlib/uart.h"

/*************************************************************************
* Project Constant and Macro Definitions
*************************************************************************/
#define BIT0            0x01
#define BIT1            0x02
#define BIT2            0x04
#define BIT3            0x08
#define BIT4            0x10
#define BIT5            0x20
#define BIT6            0x40
#define BIT7            0x80
#define GPIO_ALL 		0x000000ff

#define CR				0x0A
#define LF				0x0D

#define CRYSTAL_16MHZ (INT32U)16000000

#define SLICE_PER 10
#define DB_PORT			GPIO_PORTE_BASE
#define DB_SLICE        BIT3
#define DB_UART         BIT4
#define DB_KEY          BIT5

#define KEY_SPACE 	0x00008000
#define KEY_LEFT  	0x00002000
#define KEY_RIGHT 	0x00004000
#define KEYBITS		0xFF
#define NAVBITS		(BIT5|BIT6|BIT7)
#define KEYPORT_BASE	GPIO_PORTB_BASE
#define NAVPORT_BASE	GPIO_PORTC_BASE
/*************************************************************************
* System Header Files 
*************************************************************************/

/*************************************************************************
* Module Header Files or Declarations 
*************************************************************************/
#include "Key.h"
#include "Control.h"
#include "UART.h"
#include "SPI.h"
/************************************************************************/

#endif
