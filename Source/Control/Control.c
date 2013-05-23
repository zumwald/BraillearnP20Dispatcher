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
typedef enum{MENU,NOTES,READ,LEARN,CHAT} CNTLSTATES;
typedef enum{nNOTES,nNEW,nOLD,nSELECT}NOTESTATES;
typedef enum{rREAD,rSELECT}READSTATES;

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

/********************************************************************
* CntlInit() - Initialization routine for the control module.
********************************************************************/
void CntlInit(void){
	/*	Initialize resources	*/

}

/********************************************************************
* CntlTask() - Implements program flow according to Menu structure.
* (Public)
********************************************************************/
void CntlTask(void) {
	INT8U key, cntlFlag;
	INT16U rawKey;

	key = GetKey(&cntlFlag,&rawKey);

	switch(progState){
	/*		Menu State			*/
	default:
	case MENU:
		switch(key){
		case 'n':
		case 'N':
			progState = NOTES;
			noteState = nSELECT;
			break;
		case 'r':
		case 'R':
			progState = READ;
			readState = rSELECT;
			break;
		case 'l':
		case 'L':
			progState = LEARN;
			break;
		case 'c':
		case 'C':
			progState = CHAT;
			break;
		default:
			//	Display Menu Message
			/*	"N: Notes?
			 * 	 R: Read?
			 * 	 L: Learn?
			 * 	 C: Chat?	"
			 */
			switch(sliceCnt){
			case 0:
			default:
				sliceCnt = 0;
				break;
			}
			sliceCnt++;
			break;
		}
		break;
	/*	*	*	*	*	*	*	*/
	/*		Note State			*/
	case NOTES:
		switch(noteState){
		default:
		case nSELECT:
			switch(key){
			case 'n':
			case 'N':
				noteState = nNEW;
				break;
			case 'o':
			case 'O':
				noteState = nOLD;
				break;
			default:
				if (cntlFlag && (key == 'M')){
					progState = MENU;
				}else{}
				//	Display
				/*	"N: New?
				 *   O: Old?	"
				 */
			}
			break;
		case nNEW:
			if (!cntlFlag && (key != 'M')){
				//	get note file name (slice counting)
				// 	when LF received, noteState = NOTES
			}else{
				noteState = nSELECT;
			}
			break;
		case nOLD:
			if (cntlFlag){
				switch(key){
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
			}else if ((key == ' ') || (key == 0x0A)){
				noteState = nNOTES;
			}else{
				//	Display current note name
			}
			break;
		case nNOTES:
			if (!cntlFlag && (key != 'M')){
				//	Notes(key,rawKey);
			}else{
				progState = MENU;
			}
			break;
		}
		break;
	/*	*	*	*	*	*	*	*/
	/*		Read State			*/
	case READ:
		switch(readState){
		default:
		case rSELECT:
			if (cntlFlag){
				switch(key){
				case 'M':
					progState = MENU;
					break;
				case '<':
					//	previous doc
					break;
				case '>':
					//	next doc
					break;
				}
			}else{
				switch(key){
				case 0x0A:
				case ' ':
					readState = rREAD;
				}
			}
			break;
		case rREAD:
			if (!cntlFlag && (key != 'M')){
				//	Read()
			}else{
				readState = rSELECT;
			}
			break;
		}
		break;
	/*	*	*	*	*	*	*	*/
	/*		Learn State			*/
	case LEARN:
		if (!cntlFlag && (key != 'M')){
			//	Learn(key,rawKey);
		}else{
			progState = MENU;
		}
		break;
	/*	*	*	*	*	*	*	*/
	/*		Chat State			*/
	case CHAT:
		if (!cntlFlag && (key != 'M')){
			//	Chat(key,rawKey);
		}else{
			progState = MENU;
		}
		break;
	/*	*	*	*	*	*	*	*/
	}
}
/********************************************************************/
