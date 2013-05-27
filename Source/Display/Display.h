/*
 * Display.h
 *
 *  Created on: May 26, 2013
 *      Author: zumwald
 */

#ifndef DISPLAY_H_
#define DISPLAY_H_

/********************************************************************
* DisplayInit() - Initialization routine for the Display module.
********************************************************************/
extern void DisplayInit(void);

/********************************************************************
* DisplayTask() - The main P20 display task, addresses 4 cells
********************************************************************/
extern void DisplayTask(void);

#endif /* DISPLAY_H_ */
