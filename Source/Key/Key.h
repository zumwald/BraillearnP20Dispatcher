/********************************************************************
* Key.h - The header file for the keypad module, Key.c
* 02/08/2007 Todd Morton
* 05/19/2013 Dan Zumwalt
*********************************************************************
*********************************************************************
* Public Resources
********************************************************************/
#ifndef KEY_H_
#define KEY_H_

/********************************************************************
* 	Braille - ASCII 	lookup table	-PUBLIC
********************************************************************/
extern const INT8U UBrailleLookup[256];

/********************************************************************
* GetKey() - Returns current value of the keypad buffer then clears 
*            the buffer. Returns 0 if no key has been pressed.
********************************************************************/
extern INT8U GetKey(INT8U *cntlFlag, INT16U *rawKey);
                              
/********************************************************************
* KeyInit() - Keypad Initialization. Must run before calling KeyTask.
********************************************************************/
extern void KeyInit(void);   


/********************************************************************
* KeyTask() - The main keypad scanning task. It scans the keypad and 
*             updates the keypad buffer if a keypress was verified. 
*             This is a cooperative task that must be called with a 
*             period between: Tb/2 < Tp < (Tact-Tb)/2
********************************************************************/
extern void KeyTask(void);   
                             
#endif /*	KEY_H_	*/
