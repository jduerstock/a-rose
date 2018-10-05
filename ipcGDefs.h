/****************************************************************************/
/*																			*/
/*		ipcGDefs.h - A/ROSE Global definitions.								*/
/*																			*/
/*		Richard C. Sewill	01/05/88.										*/
/*																			*/
/*		Copyright © 1987-93,  Apple Computer, Inc.  All rights reserved.	*/
/*																			*/
/****************************************************************************/

#ifndef						_ipcGDefs_defined_
#define	_ipcGDefs_defined_

#include	"iccmDefs.h"
#include	"arose.h"
#include	"os.h"

		
/*	Symbolic definitions.	*/

#define	MaxQueues	31	/* Making this larger will fail!				*/

#define	IR_Size		1<<IR_Shift
#if		IR_Size < sizeof IR_REC  Then 
 		Aerror	The Symbol RB_Shift must be increased 
#endif 

/*	 Record block data structure - This structure is saved in IPCg.	*/

struct	RB
{
	OSlong	qLink;		/* 00 Receive request buffer link								*/
	OSlong	mId;		/* 04 Receive request message ID field - for matching			*/
	tid_type	mFrom;	/* 08 Receive request mFrom field - for matching				*/
	OSshort	mCode;		/* 0C Receive request mCode field - for matching				*/
	OSshort	index;		/* 0E index = TID - 1 associated with this record block		*/
	OSlong	Timeout;	/* 10 Receive request timeout field							*/
	OSlong	Compl;		/* 14 Receive request completion routine						*/
	OSlong	AbsTime;	/* 18 Receive request absolute timeout							*/
	OSlong	QueHead;	/* 1C Array of queue heads										*/
	OSlong	QueTail;	/* 20 Array of queue tails										*/
	OSlong	RcvIdle;	/* 24 Callers idle routine to call when waiting on a receive	*/
	OSlong	SaveA5;		/* 28 Callers A5 to be used for completion/idle routines		*/
	mMessage	*Msg;	/* 2C Message returned to Receive request						*/
	OSchar	iQFTOQs;	/* 30 Flag indicates in timeout queue							*/
	OSchar	Filler2;	/* 31 Filler													*/
	OSchar	iQFRROs;	/* 32 Flag indicates a receive request is outstanding			*/
	OSchar	iQFRMAs;	/* 33 Flag indicates receive match any							*/
	OSchar	DTRec[20];	/* 34 Deferred task record (could not find a struct!!!)		*/
};
	
		
/*	NuMacIPC Global data structure.		*/

struct	IPCg	
{
	struct	cap_Rec	iCAP;		/* Comm. area pointer							*/
	struct  ca_Rec	*iCAPhysAddr;	// physical address of comm. area
	struct mMessage *LogicalPtrs[ic_SlotMax];  // logical pointers
	OSlong	iHeads[ic_SlotMax];	/* Outbound queue head pointers								*/
	OSlong	iTails[ic_SlotMax];	/* Outbound queue tail pointers								*/
	struct RB *tcbptrs[MaxQueues+1];/* Pointers to active TID blocks							*/
	OSchar	iNQO;				/* Number of queues currently open							*/
	OSchar	iMsgLck;			/* Message interlock										*/
	OSshort	iProcessor;			/* Processor Type											*/
	OSchar	iVMActive;			/* Set non-zero if Virtual Memory is active					*/
	OSchar	iMMUActive;			/* Set non-zero if memory management active					*/
	OSchar	SlotMgrFlag;		/* Non-zero if slot manager is present						*/
	OSchar	iTRQBsy;			/* Set true if Timer/Receive queue interlocked and work		*/
	OSlong	iMsgFlag;			/* Message flag												*/
	OSlong	iMsgHead;			/* Head of message buffer list								*/
	OSlong	iMsgFwa;			/* fwa of message area										*/
	OSlong	iMsgLwa;			/* lwa of message area										*/
	OSlong	iUnique;			/* Unique message ID										*/
	OSlong	iIntID;				/* msg ID taken by user rtn during msg interlock algorithm	*/
	mMessage	*iMsgPtr;			/* Message being freed by user rtn during msg interlock		*/
	OSlong	iTOQ;				/* Timeout queue (linked through RB -> qLink)				*/
	OSlong	iBucket;			/* Number of messages discarded								*/
	OSlong	iQCount;			/* Number of times message was queued						*/
	OSlong	iRCount;			/* Messages returned										*/
	OSlong	iICount;			/* Messages received										*/
	OSlong	iOCount;			/* Messages sent											*/
	OSlong	iSCount;			/* Scan count												*/
	OSlong	QSCount[ic_SlotMax];/* Last QSCount value from active slot						*/
	OSlong	Timer;				/* Next time to check QSCount values for change				*/
	OSlong	iDCEPtr;			/* Address of our DCE										*/
	OSlong	iStackP;			/* Top of stack (Once initialized, read only)				*/
	OSlong	iStackB;			/* Bottom of stack (Once initialized, read only)			*/
	OSchar	iWaitFlag;			/* Flag indicating slots being waited for					*/
	OSchar	iFiller;			/* Reserved													*/
	OSshort	iSDly;				/* Current scan delay in ticks								*/
	OSchar	iTRQFlag;			/* Timer/Receive queue interlock							*/
	OSchar	iDrvFLS;			/* driver Global Flag we have switched to our local stack	*/
	OSchar	iDrvFSA;			/* driver Global flag Scanner is active						*/
	OSchar	scanagn;			/* Flag set non-zero if intercard interrupt					*/
	tid_type	NameTID;		/* Name manager TID											*/
	tid_type	TraceTask;		/* Trace manager TID										*/
	tid_type	IMMTID;			/* IMM Handler TID											*/
	char	*MemoryList;		/* Pointer to memory list									*/
	long	MinFreeMem;			/* Minimum amount of free memory (8 byte blocks)			*/
	long	MaxFreeMem;			/* Maximum amount of free memory (8 byte blocks)			*/
	long	AvailMemry;			/* Available memory in 8 byte blocks						*/
	mMessage	*iSentMQH;			/* Head of Sent messages queue								*/
	mMessage	*iSentMQT;			/* Tail of Sent messags queue								*/
	OSlong	ReceiveQH;			/* Entry to be linked into Receive Q head					*/
	OSlong	ReceiveQT;			/* Entry to be linked into Receive Q tail					*/
	OSlong	KillMap;			/* Bit map indicating kill receive request					*/
	OSlong	DieMap;				/* Bit map indicating die TID request						*/
	struct	MemMap *iMemMap;	/* Local card memory map									*/
	struct RB	*ComplQH;		/* Head of completion routine queue							*/
	struct RB	*ComplQT;		/* Tail of completion routine queue							*/
	struct RB	UnregBlock;		/* Name Manager Unregister Block							*/
	struct RB	IMMBlock;		/* IMM Call Block											*/
	OSshort	FreeMsgCount;		/* Number of free message buffers							*/
	struct RB	iRcvBuf[MaxQueues+1];
	OSchar	IntTbl[IR_Size*(ic_SlotMax-IR_SlotBias)];
	OSchar	MemFlag;			/* Memory region/buffer manipulated flag					*/
	OSchar	BadCard[ic_SlotMax];/* Flags indicate whether card violates 32 bit protocol		*/
	OSlong	fNameListHdl;		/* File name list handle									*/
	struct	ca_Rec	iCA;		/* Storage for communication area							*/
};


/*	Function declarations	*/

extern struct IPCg *GetIPCg();/* Returns the pointer to IPC global area.  Note that the value */
							/* returned points at the first word of the IPC global area.	*/
							/* The declaration for ipcGdefs.a is offset by IPCg.nSize		*/
							/* Warning - in asm, the value IPCg.nSize must be added.		*/

#endif

/*		End of ipcGDefs.a		*/
