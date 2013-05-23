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
const INT8U menuStr[36][10] = {"\r _       ","        _ ","_ _      _","_____     ","     _____","  _   _ \r\n",
						   "\r| |      ","       (_)"," | |    | "," ____|   /","\\   |  __ ","\\| \\ | |\r\n",
						   "\r| |__  _ ","__ __ _ _|"," | |    | ","|__     / "," \\  | |__)"," |  \\| |\r\n",
						   "\r| '_ \\| '","__/ _` | |"," | |    | "," __|   / /","\\ \\ |  _  ","/| . ` |\r\n",
						   "\r| |_) | |"," | (_| | |"," | |____| ","|____ / __","__ \\| | \\ ","\\| |\\  |\r\n",
						   "\r|_.__/|_|","  \\__,_|_|","_|______|_","_____/_/  ","  \\_\\_|  \\","_\\_| \\_|\r\n"};
/*const  INT8U menuStr[5][59] = { "| |             (_) | |    |  ____|   /\\   |  __ \\| \\ | |\r\n",
								"| |__  _ __ __ _ _| | |    | |__     /  \\  | |__) |  \\| |\r\n",
								"| '_ \\| '__/ _` | | | |    |  __|   / /\\ \\ |  _  /| . ` |\r\n",
								"| |_) | | | (_| | | | |____| |____ / ____ \\| | \\ \\| |\\  |\r\n",
								"|_.__/|_|  \\__,_|_|_|______|______/_/    \\_\\_|  \\_\\_| \\_|\r\n"};*/
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
				UARTSend((INT8U *)menuStr[0],(INT32U)sizeof(menuStr[0]));
				break;
			case 1:
				UARTSend((INT8U *)menuStr[1],(INT32U)sizeof(menuStr[1]));
				break;
			case 2:
				UARTSend((INT8U *)menuStr[2],(INT32U)sizeof(menuStr[2]));
				break;
			case 3:
				UARTSend((INT8U *)menuStr[3],(INT32U)sizeof(menuStr[3]));
				break;
			case 4:
				UARTSend((INT8U *)menuStr[4],(INT32U)sizeof(menuStr[4]));
				break;
			case 5:
				UARTSend((INT8U *)menuStr[5],(INT32U)sizeof(menuStr[5]));
				break;
			case 6:
				UARTSend((INT8U *)menuStr[6],(INT32U)sizeof(menuStr[6]));
				break;
			case 7:
				UARTSend((INT8U *)menuStr[7],(INT32U)sizeof(menuStr[7]));
				break;
			case 8:
				UARTSend((INT8U *)menuStr[8],(INT32U)sizeof(menuStr[8]));
				break;
			case 9:
				UARTSend((INT8U *)menuStr[9],(INT32U)sizeof(menuStr[9]));
				break;
			case 10:
				UARTSend((INT8U *)menuStr[10],(INT32U)sizeof(menuStr[10]));
				break;
			case 11:
				UARTSend((INT8U *)menuStr[11],(INT32U)sizeof(menuStr[11]));
				break;
			case 12:
				UARTSend((INT8U *)menuStr[12],(INT32U)sizeof(menuStr[12]));
				break;
			case 13:
				UARTSend((INT8U *)menuStr[13],(INT32U)sizeof(menuStr[13]));
				break;
			case 14:
				UARTSend((INT8U *)menuStr[14],(INT32U)sizeof(menuStr[14]));
				break;
			case 15:
				UARTSend((INT8U *)menuStr[15],(INT32U)sizeof(menuStr[15]));
				break;
			case 16:
				UARTSend((INT8U *)menuStr[16],(INT32U)sizeof(menuStr[16]));
				break;
			case 17:
				UARTSend((INT8U *)menuStr[17],(INT32U)sizeof(menuStr[17]));
				break;
			case 18:
				UARTSend((INT8U *)menuStr[18],(INT32U)sizeof(menuStr[18]));
				break;
			case 19:
				UARTSend((INT8U *)menuStr[19],(INT32U)sizeof(menuStr[19]));
				break;
			case 20:
				UARTSend((INT8U *)menuStr[20],(INT32U)sizeof(menuStr[20]));
				break;
			case 21:
				UARTSend((INT8U *)menuStr[21],(INT32U)sizeof(menuStr[21]));
				break;
			case 22:
				UARTSend((INT8U *)menuStr[22],(INT32U)sizeof(menuStr[22]));
				break;
			case 23:
				UARTSend((INT8U *)menuStr[23],(INT32U)sizeof(menuStr[23]));
				break;
			case 24:
				UARTSend((INT8U *)menuStr[24],(INT32U)sizeof(menuStr[24]));
				break;
			case 25:
				UARTSend((INT8U *)menuStr[25],(INT32U)sizeof(menuStr[25]));
				break;
			case 26:
				UARTSend((INT8U *)menuStr[26],(INT32U)sizeof(menuStr[26]));
				break;
			case 27:
				UARTSend((INT8U *)menuStr[27],(INT32U)sizeof(menuStr[27]));
				break;
			case 28:
				UARTSend((INT8U *)menuStr[28],(INT32U)sizeof(menuStr[28]));
				break;
			case 29:
				UARTSend((INT8U *)menuStr[29],(INT32U)sizeof(menuStr[29]));
				break;
			case 30:
				UARTSend((INT8U *)menuStr[30],(INT32U)sizeof(menuStr[30]));
				break;
			case 31:
				UARTSend((INT8U *)menuStr[31],(INT32U)sizeof(menuStr[31]));
				break;
			case 32:
				UARTSend((INT8U *)menuStr[32],(INT32U)sizeof(menuStr[32]));
				break;
			case 33:
				UARTSend((INT8U *)menuStr[33],(INT32U)sizeof(menuStr[33]));
				break;
			case 34:
				UARTSend((INT8U *)menuStr[34],(INT32U)sizeof(menuStr[34]));
				break;
			case 35:
				UARTSend((INT8U *)menuStr[35],(INT32U)sizeof(menuStr[35]));
				break;
			case 36:
				UARTSend((INT8U *)menuStr[36],(INT32U)sizeof(menuStr[36]));
				break;
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
