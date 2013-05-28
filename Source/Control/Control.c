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

/********************************************************************
 * Public Resources
 ********************************************************************/
void CntlTask(void);

/********************************************************************
 * Private Resources
 ********************************************************************/
static CNTLSTATES progState;
static NOTESTATES noteState;
static READSTATES readState;
static INT32U sliceCnt;
static INT8U bMenuDisplayed;

static INT8U displayBuffer[DISPLAYLEN];
static INT8U displayIndex;

static INT8U chatRxBuffer[UARTBUFFERSIZE], chatTxBuffer[UARTBUFFERSIZE];
static INT8U chatRxIndex, chatTxIndex;

/*	file system resources	*/
static FILETABLESTRUCT fileLookupTable[NUMFILES];	// Index of files
static FILETABLESTRUCT tmpFile;	//	RAM copy of current filetable
static FILESTRUCT tmpFileData;
static INT32U tmpFIndex;

const INT8U learnString[] =
		"the quick brown fox jumped over the lazy brown dog. THE QUICK BROWN FOX JUMPED OVER THE LAZY BROWN DOG!";

/********************************************************************
 * InitTmpVars() - Initialization routine for between states.
 ********************************************************************/
void InitTmpVars(void) {

	sliceCnt = 0;
	bMenuDisplayed = FALSE;
	displayIndex = 0;
	chatRxIndex = 0;
	chatTxIndex = 0;
	tmpFile.state = fUNUSED;
	tmpFile.tableIndex = 0;
	tmpFIndex = 0;
}

/********************************************************************
 * FindNextFile() - returns true if success, false if no files exist.
 * 					next = TRUE, look forward. next = FALSE, look back.
 ********************************************************************/
INT8U FindNextFile(FILETABLESTRUCT *current, INT8U next) {

	INT16S i;
	INT8U curindex = current->tableIndex;
	FILESTATES fState = current->state;

	if (next) {
		//	curindex + 1 to end
		for (i = curindex + 1; i < NUMFILES; i++) {
			if (fileLookupTable[i].state & fState) {
				*current = fileLookupTable[i];
				return (INT8U) TRUE;
			} else {
			}
		}
		//	beginning to curindex - 1
		for (i = 0; i < curindex + 1; i++) {
			if (fileLookupTable[i].state & fState) {
				*current = fileLookupTable[i];
				return (INT8U) TRUE;
			} else {
			}
		}
		return (INT8U) FALSE;
	} else {
		//	curindex to beginning
		for (i = curindex; i >= 0; i--) {
			if (fileLookupTable[i].state & fState) {
				*current = fileLookupTable[i];
				return (INT8U) TRUE;
			} else {
			}
		}
		//	end to curindex + 1
		for (i = NUMFILES; i > curindex; i--) {
			if (fileLookupTable[i].state & fState) {
				*current = fileLookupTable[i];
				return (INT8U) TRUE;
			} else {
			}
		}
		return (INT8U) FALSE;
	}
}

/********************************************************************
 * GetNextFile() - returns pointer to next unused file table or null
 * 					if they are all full.
 ********************************************************************/
FILETABLESTRUCT GetNextFile(INT8U *err) {

	INT8U i;
	for (i = 0; i < NUMFILES; i++) {
		if (fileLookupTable[i].state == fUNUSED) {
			*err = FALSE;
			return fileLookupTable[i];
		} else {
		}
	}
	*err = TRUE;
	return fileLookupTable[0];
}

/********************************************************************
 * CntlInit() - Initialization routine for the control module.
 ********************************************************************/
void CntlInit(void) {
	/*	Initialize resources	*/
	progState = MENU;
	noteState = nSELECT;
	readState = rSELECT;
	sliceCnt = 0;
	bMenuDisplayed = FALSE;

	displayIndex = 0;

	chatRxIndex = 0;
	chatTxIndex = 0;

	FileInit((FILETABLESTRUCT *) &fileLookupTable);
	tmpFile.state = fUNUSED;
	tmpFile.tableIndex = 0;
	tmpFIndex = 0;
}

/********************************************************************
 * CntlTask() - Implements program flow according to Menu structure.
 * (Public)
 ********************************************************************/
void CntlTask(void) {
	INT8U key, cntlFlag, error;
	INT16U rawKey;

	key = GetKey(&cntlFlag, &rawKey);

	//	DEBUG
	if (key) {
		UARTSend("Key: ", (INT32U) 5);
		UARTSend(&key, (INT32U) 1);
		UARTSend("\r\n", (INT32U) 2);
		(void) SPISendChar((INT8U) rawKey);
	} else {
	}
	//	-----

	switch (progState) {
	/*		Menu State			*/	//TODO Menu State
	default:
	case MENU:
		switch (key) {
		case 'n':
		case 'N':
			progState = NOTES;
			noteState = nSELECT;
			UARTSend("\r\nNotes", (INT32U) 7);
			DisplayUpdate("Notes");
			InitTmpVars();
			break;
		case 'r':
		case 'R':
			progState = READ;
			readState = rSELECT;
			UARTSend("\r\nRead", (INT32U) 6);
			DisplayUpdate("Read");
			InitTmpVars();
			break;
		case 'l':
		case 'L':
			progState = LEARN;
			UARTSend("\r\nLearn", (INT32U) 7);
			DisplayUpdate("Learn");
			InitTmpVars();
			break;
		case 'c':
		case 'C':
			progState = CHAT;
			UARTSend("\r\nChat", (INT32U) 6);
			DisplayUpdate("Chat");
			InitTmpVars();
			break;
		default:
			//	Display Menu Message
			/*	"N: Notes?
			 * 	 R: Read?
			 * 	 L: Learn?
			 * 	 C: Chat?	"
			 */
			if ((!bMenuDisplayed) || (sliceCnt > ONEMINUTE)) {
				switch (sliceCnt) {
				case 0:
					UARTSend("Main Menu\r\n", (INT32U) 11);
					DisplayUpdate("Menu");
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
					break;
				case ONESECOND:
					DisplayUpdate("[N]otes");
					break;
				case TWOSECONDS:
					DisplayUpdate("[R]ead");
					break;
				case THREESECONDS:
					DisplayUpdate("[L]earn");
					break;
				case FOURSECONDS:
					DisplayUpdate("[C]hat");
					break;
				case FIVESECONDS:
					DisplayClear();
					break;
				default:
					if (sliceCnt > SIXSECONDS) {
						sliceCnt = 0;
						bMenuDisplayed = TRUE;
					} else {
					}
					break;
				}
			} else {
			}
			break;
		}
		break;
		/*	*	*	*	*	*	*	*/
		/*		Note State			*/	//TODO Notes State
	case NOTES:
		/*	Allow message time to settle	*/
		if (sliceCnt > ONESECOND) {
			switch (noteState) {
			default:
			case nSELECT:
				switch (key) {
				case 'n':
				case 'N':
					noteState = nNEW;
					break;
				case 'o':
				case 'O':
					noteState = nOLD;
					break;
				default:
					if (cntlFlag && (key == 'M')) {
						progState = MENU;
						InitTmpVars();
					} else {
						//	Display
						/*	"N: New?
						 *   O: Old?	"
						 */
						if ((!bMenuDisplayed) || (sliceCnt > ONEMINUTE)) {
							switch (sliceCnt) {
							case 0:
								UARTSend("\r\n[N]ew", (INT32U) 7);
								DisplayUpdate("[N]ew");
								break;
							case 1:
								UARTSend("\r\n[O]ld", (INT32U) 7);
								break;
							case TWOSECONDS:
								DisplayUpdate("[O]ld");
								break;
							case FOURSECONDS:
								DisplayClear();
								break;
							default:
								if (sliceCnt > FOURSECONDS) {
									sliceCnt = 0;
									bMenuDisplayed = FALSE;
								} else {
								}
							}
						} else {
						}
					}
				}
				break;
			case nNEW:
				if (!cntlFlag && (key != 'M')) {
					//	get note file name (slice counting)
					// 	when LF received, noteState = NOTES
					//	Ignore keys until menu displayed for user
					if ((!bMenuDisplayed) || (sliceCnt > ONEMINUTE)) {
						switch (sliceCnt) {
						case 0:
							UARTSend("\r\nName: ", (INT32U) 8);
							DisplayUpdate("Name: ");
							/*	Get current file pointer	*/
							tmpFile = GetNextFile(&error);
							if (error == TRUE) {
								/*	Error, memory full	*/
								progState = MENU;
								InitTmpVars();
							} else {
								tmpFile.state = fNOTES;
							}
							break;
						case ONESECOND:
							bMenuDisplayed = TRUE;
							break;
						default:
							if (sliceCnt > ONESECOND) {
								sliceCnt = 0;
								bMenuDisplayed = FALSE;
							} else {
							}
						}
					} else {
						/*	Menu has been displayed, looking for keys now	*/
						/*	by state mutex, we can use for tmpFIndex as our
						 *  index for the name field in the filetable entry.
						 */
						switch (key) {
						default:
							if (key == 0) {
								break;
							} else {
								tmpFile.name[tmpFIndex++] = key;
								if (tmpFIndex < BUFFERLEN) {
									break;
								} else {
								}					//	fall through
							}
						case '\r':
						case '\n':
							//	got name, moving on into NOTES mode
							if (tmpFIndex != 0) {
								tmpFIndex = 0;
								noteState = nNOTES;
							} else {
							}
							break;
						}
					}
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
						//	if not uninitialized
						if (tmpFile.state != fUNUSED) {
							error = FindNextFile(&tmpFile, BACK);
						} else {
							error = FindNextFile(&tmpFile, BACK);
						}
						break;
					case '>':
						if (tmpFile.state != fUNUSED) {
							error = FindNextFile(&tmpFile, FORWARD);
						} else {
							error = FindNextFile(&tmpFile, FORWARD);
						}
						break;
					}
					if (error == TRUE) {
						//	no old notes go back to select
						UARTSend("\r\nNo Old Notes", (INT32U) 14);
						DisplayUpdate("No Notes");
						noteState = nSELECT;
						break;
					} else {
						UARTSend(tmpFile.name, (INT32U) 16);
						DisplayUpdate(tmpFile.name);
					}
				} else if ((key == ' ') || (key == '\r') || (key == '\n')) {
					if (tmpFile.state != fUNUSED) {
						noteState = nNOTES;
					} else {
					}
				} else {
				}
				break;
			case nNOTES:
				if (!cntlFlag && (key != 'M') && (tmpFIndex < FILEBLOCKSIZE)) {
					if (!cntlFlag) {	// ignore Nav keys
						tmpFileData[tmpFIndex++] = key;
						DisplayAppendChar(key);
					} else {
					}
				} else {
					//	Save this note
					fileLookupTable[tmpFile.tableIndex] = tmpFile;
					(void) FileUpdate(&fileLookupTable[tmpFile.tableIndex],
							(FILESTRUCT *) tmpFileData);
					progState = MENU;
					InitTmpVars();
				}
				break;
			}
			break;
		} else {
		}
		/*	*	*	*	*	*	*	*/
		/*		Read State			*/
	case READ:
		if (sliceCnt > ONESECOND) {
			switch (readState) {
			default:
			case rSELECT:
				if (cntlFlag) {
					switch (key) {
					case 'M':
						progState = MENU;
						InitTmpVars();
						break;
					case '<':
						if (tmpFile.state == fUNUSED) {
							error = FindNextFile(&tmpFile, BACK);
						} else {
							error = FindNextFile(&tmpFile, BACK);
						}
						break;
					case '>':
						if (tmpFile.state == fUNUSED) {
							error = FindNextFile(&tmpFile, FORWARD);
						} else {
							error = FindNextFile(&tmpFile, FORWARD);
						}
						break;
					}
					if (error == TRUE) {
						//	no old notes go back to select
						UARTSend("\r\nNo Old Docs", (INT32U) 14);
						DisplayUpdate("No Docs");
						readState = rSELECT;
						break;
					} else {
						UARTSend(tmpFile.name, (INT32U) 16);
						DisplayUpdate(tmpFile.name);
					}
				} else {
					switch (key) {
					case '\r':
					case '\n':
					case ' ':
						if (tmpFile.state != fUNUSED) {
							readState = rREAD;
						} else {
						}
					}
				}
				break;
			case rREAD:
				if (!cntlFlag && (key != 'M')) {
					if (cntlFlag && (key == '<')) {
						if (tmpFIndex < DISPLAYLEN) {
							/*	ignore	*/
						} else {
							tmpFIndex -= DISPLAYLEN;
						}
					} else if (cntlFlag && (key == '>')) {
						if (tmpFIndex > FILEBLOCKSIZE - DISPLAYLEN) {
							/*	ignore	*/
						} else {
							tmpFIndex += DISPLAYLEN;
						}
					}
					DisplayUpdate((INT8U *) (tmpFile.ptr + tmpFIndex));
				} else {
					readState = rSELECT;
				}
				break;
			}
			break;
		} else {
		}
		/*	*	*	*	*	*	*	*/
		/*		Learn State			*/
	case LEARN:
		if (sliceCnt > ONESECOND) {
			if (!cntlFlag && (key != 'M')) {
				if (key != learnString[tmpFIndex]) {
					DisplayBlinkMiss();
				} else {
					if (learnString[++tmpFIndex] == 0x00) {
						progState = MENU;
						InitTmpVars();
					} else {
					}
				}
			} else {
				progState = MENU;
				InitTmpVars();
			}
		} else {
		}
		UARTSend("\r\n", (INT32U) 2);
		UARTSend(learnString + tmpFIndex, (INT32U) 8);
		DisplayUpdate((INT8U *)(learnString + tmpFIndex));
		break;
		/*	*	*	*	*	*	*	*/
		/*		Chat State			*/
	case CHAT:
		if (!cntlFlag && (key != 'M')) {
			/*	Get Chat message	*/
			UARTGetBuffer(chatRxBuffer);
			if (*chatRxBuffer != 0x00) {
				DisplayUpdate(chatRxBuffer);
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
			InitTmpVars();
		}
		break;
		/*	*	*	*	*	*	*	*/
	}
	sliceCnt++;
}
/********************************************************************/
