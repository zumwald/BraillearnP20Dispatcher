/*
 * FileIO.h
 *
 *  Created on: May 27, 2013
 *      Author: Dan Zumwalt
 ********************************************************************
* Public Resources
********************************************************************/
#ifndef FILEIO_H_
#define FILEIO_H_

typedef enum {
	fREAD = 0x01, fNOTES = 0x02, fLEARN = 0x04, fUNUSED = 0x08
} FILESTATES;

typedef INT8U FILESTRUCT[FILEBLOCKSIZE];

typedef struct {
	INT16U		tableIndex;
	FILESTATES 	state;// = fUNUSED;
	INT8U 		name[BUFFERLEN];// = "               ";
	FILESTRUCT	*ptr;// = 0x00;
}	FILETABLESTRUCT;

/********************************************************************
* FileInit() - FileIO Initialization. Must run before any fileIO
********************************************************************/
extern void FileInit(FILETABLESTRUCT *fileTblStruct);

/********************************************************************
* FileUpdate() - writes current file data to FLASH, returns true if
* 				 successful false if otherwise.
********************************************************************/
extern INT8U FileUpdate(FILETABLESTRUCT *fileTblStruct, FILESTRUCT *data);

#endif /* FILEIO_H_ */
