/*
 * Control.c
 *
 *  Created on: May 19, 2013
 *      Author: Dan Zumwalt
 */
/********************************************************************
 * Project master header file
 ********************************************************************/
#include "includes.h"

/********************************************************************
 * Module Defines
 ********************************************************************/
typedef enum {
	MENU, NOTES, READ, LEARN, CHAT
} CNTLSTATES;
typedef enum {
	nNOTES, nNEW, nOLD, nSELECT
} NOTESTATES;
typedef enum {
	rREAD, rSELECT
} READSTATES;
#define 	BUFFERSIZE	16

/********************************************************************
 * Public Resources
 ********************************************************************/
void CntlTask(void);

/********************************************************************
 * Private Resources
 ********************************************************************/
static CNTLSTATES progState = MENU;
static NOTESTATES noteState = nSELECT;
static READSTATES readState = rSELECT;
static INT32U sliceCnt = 0;
static INT8U bMenuDisplayed = FALSE;

/********************************************************************
 * CntlInit() - Initialization routine for the control module.
 ********************************************************************/
void CntlInit(void) {
	/*	Initialize resources	*/

}

/********************************************************************
 * CntlTask() - Implements program flow according to Menu structure.
 * (Public)
 ********************************************************************/
void CntlTask(void) {
	INT8U key, cntlFlag;
	INT16U rawKey;
	static INT8U readBuffer[BUFFERSIZE];
	//static INT8U sendBuffer[BUFFERSIZE];
	//INT8U* rBptr = readBuffer;
	//INT8U* sBptr = sendBuffer;

	key = GetKey(&cntlFlag, &rawKey);

	if (key) {
		UARTSend("Key: ", (INT32U) 5);
		UARTSend(&key, (INT32U) 1);
		UARTSend("\r\n",(INT32U)2);
		(void)SPISendChar((INT8U)rawKey,(INT8U)0x00);
	} else {
	}

	switch (progState) {
	/*		Menu State			*/
	default:
	case MENU:
		switch (key) {
		case 'n':
		case 'N':
			progState = NOTES;
			noteState = nSELECT;
			UARTSend("\r\nNotes", (INT32U) 7);
			break;
		case 'r':
		case 'R':
			progState = READ;
			readState = rSELECT;
			UARTSend("\r\nRead", (INT32U) 6);
			break;
		case 'l':
		case 'L':
			progState = LEARN;
			UARTSend("\r\nLearn", (INT32U) 7);
			break;
		case 'c':
		case 'C':
			progState = CHAT;
			UARTSend("\r\nChat", (INT32U) 6);
			break;
		default:
			//	Display Menu Message
			/*	"N: Notes?
			 * 	 R: Read?
			 * 	 L: Learn?
			 * 	 C: Chat?	"
			 */
			if ((!bMenuDisplayed) || (sliceCnt > 6000)) {
				switch (sliceCnt) {
				case 0:
					UARTSend("Main Menu\r\n", (INT32U) 11);
					break;
				case 1:
					UARTSend("[N]otes     ", (INT32U) 12);
					break;
				case 2:
					UARTSend("[R]ead     ", (INT32U) 11);
					break;
				case 3:
					UARTSend("[L]earn     ", (INT32U) 12);
					break;
				case 4:
					UARTSend("[C]hat\r\n", (INT32U) 8);
					bMenuDisplayed = TRUE;
					break;
				default:
					sliceCnt = 0;
					break;
				}
			}
			sliceCnt++;
			break;
		}
		break;
		/*	*	*	*	*	*	*	*/
		/*		Note State			*/
	case NOTES:
		switch (noteState) {
		default:
		case nSELECT:
			switch (key) {
			case 'n':
			case 'N':
				noteState = nNEW;
				UARTSend("\r\nNew Note", (INT32U) 10);
				break;
			case 'o':
			case 'O':
				noteState = nOLD;
				UARTSend("\r\nOld Note", (INT32U) 10);
				break;
			default:
				if (cntlFlag && (key == 'M')) {
					progState = MENU;
					bMenuDisplayed = FALSE;
				} else {
				}
				//	Display
				/*	"N: New?
				 *   O: Old?	"
				 */
			}
			break;
		case nNEW:
			if (!cntlFlag && (key != 'M')) {
				//	get note file name (slice counting)
				// 	when LF received, noteState = NOTES
			} else {
				noteState = nSELECT;
			}
			break;
		case nOLD:
			if (cntlFlag) {
				switch (key) {
				case 'M':
					noteState = nSELECT;
					break;
				case '<':
					//	previous note
					break;
				case '>':
					//	next note
					break;
				}
			} else if ((key == ' ') || (key == 0x0A)) {
				noteState = nNOTES;
			} else {
				//	Display current note name
			}
			break;
		case nNOTES:
			if (!cntlFlag && (key != 'M')) {
				//	Notes(key,rawKey);
			} else {
				progState = MENU;
				bMenuDisplayed = FALSE;
			}
			break;
		}
		break;
		/*	*	*	*	*	*	*	*/
		/*		Read State			*/
	case READ:
		switch (readState) {
		default:
		case rSELECT:
			if (cntlFlag) {
				switch (key) {
				case 'M':
					progState = MENU;
					bMenuDisplayed = FALSE;
					break;
				case '<':
					//	previous doc
					break;
				case '>':
					//	next doc
					break;
				}
			} else {
				switch (key) {
				case 0x0A:
				case ' ':
					readState = rREAD;
				}
			}
			break;
		case rREAD:
			if (!cntlFlag && (key != 'M')) {
				//	Read()
			} else {
				readState = rSELECT;
			}
			break;
		}
		break;
		/*	*	*	*	*	*	*	*/
		/*		Learn State			*/
	case LEARN:
		if (!cntlFlag && (key != 'M')) {
			//	Learn(key,rawKey);
		} else {
			progState = MENU;
			bMenuDisplayed = FALSE;
		}
		break;
		/*	*	*	*	*	*	*	*/
		/*		Chat State			*/
	case CHAT:
		if (!cntlFlag && (key != 'M')) {
			/*	Get Chat message	*/
			UARTGetBuffer(readBuffer);
			if (*readBuffer != 0x00) {
				//	TODO display buffer
			} else {
			}

			/*	Send user key	*/
			if (!cntlFlag || key == ' ') {
				UARTSendChar(key);
			} else {
				//	TODO respond to nav key
			}
		} else {
			progState = MENU;
			bMenuDisplayed = FALSE;
		}
		break;
		/*	*	*	*	*	*	*	*/
	}
}
/********************************************************************/
