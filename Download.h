/********************************************************************************/
/*																				*/
/*						Download.h - - download constants.						*/
/*																				*/
/*			Richard W. Mincher.								87/08/28.			*/
/*			Richard C. Sewill.								87/11/23.			*/
/*			Anumele D. Raja.								89/08/07.			*/
/*																				*/
/*			Changes:															*/
/*																				*/
/*				C++ friendly.  Modified return status values					*/
/*																				*/
/*		Copyright © 1987-88, Apple Computer, Inc. 		All rights reserved.	*/
/*																				*/
/********************************************************************************/

#include "os.h"
#include "arose.h"

#ifndef	_Download_defined_
#define	_Download_defined_

/* Error Constants */

#define	DLE_NOERR		0		/*	No error					*/
#define	DLE_NOJT		1		/*	No jump table found			*/
#define	DLE_DATAINIT	2		/*	Bad Data Init segment		*/
#define	DLE_GLOBALF		3		/*	Global data format error	*/
#define	DLE_CODES		4		/*	Code segment error			*/
#define	DLE_MAC2		5		/*	Can only run on Mac II		*/
#define	DLE_EMPTY		6		/*	No cards found				*/
#define	DLE_NOCARD		7		/*	Slot specified is empty		*/
#define	DLE_RESFILE		8		/*	Couldn't open resource file	*/
#define	DLE_FILEWRONG	9		/*	Download file is wrong type	*/
#define DLE_STARTERR	10		/*  Starting error				*/
#define DLE_NOMEM		11		/*  No memory					*/
#define DLE_RSMERR		12		/*  RSM error					*/
#define DLE_NORSM		13		/*  No RSM						*/
#define DLE_NOAROSE		14		/*  No A/ROSE running on card		*/
#define DLE_NORSRC		15		/*  No 'CNFG' resource			*/
#define DLE_NOPREP		16		/*  No A/ROSE prep file			*/
#define DLE_ABORT		17		/*  Download aborted			*/


/* Useful constants */

#define	Max_Slots		16		/*	Maximum number of card slots	*/

/*	Flags to control download options.		*/

#define DL_INITLOAD		1		/* if (options & DL_INITLOAD) then initial load else dynamic load  */
#define DL_CLEARMEM		2		/* if (options & DL_CLEARMEM) then low memory cleared if initial load  */

#define DEF_ADDROFFSET	0x0		/* default address offset  */
#define DEF_LOADADDR	0x800	/* default load address  */
#define DEF_GCOMMON		(struct gCommon *)0x400	/* default gCommon area  */

typedef pascal void (*PascalPtr)(short sh);	
typedef pascal void (*PascalPtrLong)(long segSize);

#ifndef ResType
#include <Types.h>
#endif

/* Routine declarations */

#ifndef applec	MPW 2.0 C

#ifdef __safe_link
extern "C" {
#endif

pascal short NewDownload(slotNum, addrOffset, loadaddr, gCommonAddr, options, type, registers, ProgProc )
	short	slotNum;
	long addrOffset;
	long loadaddr;
	struct gCommon *gCommonAddr;
	short options;
	ResType	type;
	struct ST_Registers *registers;
	PascalPtrLong ProgProc;
	extern;
	
pascal tid_type DynamicDownload(slotNum, type, st_prmblock, startParmSegment, lenParmSegment)
	short	slotNum;
	ResType	type;
	struct	ST_PB	*st_prmblock;
	char *startParmSegment;
	long	lenParmSegment;
	extern;
	
pascal short Findcard(slot, type)
	short	*slot;
	long type;
	extern;

pascal short NewFindcard(slot, type)
short *slot, type;
extern;

pascal long DLMem (restype)
	ResType	restype;
	extern;

pascal short HaltCard(slotNUM)
	short slotNUM;
	extern;

pascal short StartCard(slotNUM)
	short slotNUM;
	extern;

pascal tid_type StartAROSE(slotNUM)
	short slotNUM;
	extern;

short TestSlot();

#ifdef __safe_link
}
#endif

#else

#ifdef __safe_link
extern "C" {
#endif

extern pascal short NewDownload(short, long, long, struct gCommon *, short, ResType,
			struct ST_Registers *, PascalPtrLong);
	
extern pascal tid_type DynamicDownload(short, ResType, struct ST_PB *, char *, long);
	
extern pascal short Findcard(short *, long);

extern pascal short NewFindcard(short *, short);

extern pascal long DLMem (ResType);

extern pascal short HaltCard(short);

extern pascal short StartCard(short);

extern pascal tid_type StartAROSE(short);

short TestSlot(short slotNUM, short *boardID, unsigned long lenMem[1], unsigned long startMem[1], short CPURsrc[4], short networkRsrc[4]);

#ifdef __safe_link
}
#endif

#endif

#endif _Download_defined_