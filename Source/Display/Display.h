/*
 * Display.h
 *
 *  Created on: May 27, 2013
 *      Author: zumwald
 */

#ifndef DISPLAY_H_
#define DISPLAY_H_

/********************************************************************
 * DisplayUpdate() - Sets DisplayBuffer to the ASCII data specified
 * 		- public
 ********************************************************************/
extern void DisplayUpdate(INT8U data[DISPLAYLEN]);

/********************************************************************
 * DisplayClear() - Clears display.
 * 		- public
 ********************************************************************/
extern void DisplayClear(void);

/********************************************************************
 * DisplayBlinkMiss() - sends command to follower to blink first
 * 						char on display, indicating a 'miss' to user
 * 						while in "LEARN" mode.
 * 		- public
 ********************************************************************/
extern void DisplayBlinkMiss(void);

/********************************************************************
 * DisplayAppendChar() - Shifts given char into end of display
 * 		- public
 ********************************************************************/
extern void DisplayAppendChar(INT8U key);

/********************************************************************
 * DisplayInit() - Display Initialization. Must run before calling
 * 				   display functions.
 * 		- public
 ********************************************************************/
extern void DisplayInit(void);

/********************************************************************
 * DisplayTask() - Updates display according to UpdateDisplay
 * (Public)
 ********************************************************************/
extern void DisplayTask(void);

/*******************************************************************/

#endif /* DISPLAY_H_ */
