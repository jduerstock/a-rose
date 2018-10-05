/****************************************************************************/
/*																			*/
/*				arose.h -  A/ROSE definition file for internal use.				*/
/*																			*/
/*						Richard W. Mincher.		87/03/15.					*/
/*																			*/
/*			Copyright © 1987-88,  Apple Computer, Inc.  All rights reserved.*/
/*																			*/
/****************************************************************************/

/*			Constants		*/

#ifndef	_arose_defined_
#define	_arose_defined_

#include	"os.h"

#define		cVersion	0x0101			/*	Release 1, version 1		*/
#define		cMaxMsg		500				/*	Maximum number of messages	*/
#define		cOSStack	4096			/*	size of OS Stack			*/
#define		cMaxTask	256				/*	Maximum Number of tasks		*/
#define		cMaxPri		32				/*	Maximum task priority		*/
#define		cTraceSize	0x1000			/*	Trace buffer size in bytes	*/

/*			Error messages		*/


#define		eCAPT		0x80000001		/*	Can't allocate process table	*/
#define		eCAIT		0x80000002		/*	Can't allocate idle task		*/
#define		eNPTR		0x80000003		/*	No processes to run				*/
#define		eBTHH		0x80000004		/*	Bad things have happened		*/
#define		eCAMS		0x80000005		/*	Can't allocate message space	*/
#define		eCAPR		0x80000006		/*	Can't allocate priority table	*/
#define		eOVFL		0x80000007		/*	Stack overflow detected			*/
#define		eMEMB		0x80000008		/*	Attempt to free bad memory buffer */
#define		eFMSG		0x80000009		/*	Attempt to free bad message buffer */
#define		eSMSG		0x8000000A		/*	Attempt to send bad message buffer */
#define		eTIMQ		0x8000000B		/*	Task not in timer queue			*/
#define		eSTTI		0x8000000C		/*	StartTask cannot be called from interrupt */
#define		eSTPI		0x8000000D		/*	StopTask cannot be called from interrrupt */
#define		eBVER		0x8000000E		/*	Download and A/ROSE versions not compatible	*/
#define		eBCPY		0x8000000F		/*	CopyNuBus may no longer be used			*/
#define		eCNST		0x80000010		/*	Cannot restart O/S, it was already running */

/*			Trap definitions	*/

#define		trUnused5		0
#define		trUnused4		1
#define		trFreeMsg		2
#define		trGetMsg		3
#define		trSpl			4
#define		trSend			5
#define		trReceive		6
#define		trStartTask		7
#define		trStopTask		8
#define		trResched		9
#define		trSpecReqs		10
#define		trFreeMem		11
#define		trGetMem		12
#define		trUnused2		13
#define		trUnused1		14
#define		trUnused3		15

/*			Trap vector address definitions		*/

#define		taUnused5		0x80
#define		taUnused4		0x84
#define		taFreeMsg		0x88
#define		taGetMsg		0x8C
#define		taSpl			0x90
#define		taSend			0x94
#define		taReceive		0x98
#define		taStartTask		0x9C
#define		taStopTask		0xA0
#define		taResched		0xA4
#define		taSpecReqs		0xA8
#define		taFreeMem		0xAC
#define		taGetMem		0xB0
#define		taUnused2		0xB4
#define		taUnused1		0xB8
#define		taUnused3		0xBC

	/*			Kinds of processors		*/

#define		type68000		0		/*	68000 processor */
#define		type68020		1		/*	68020 processor	*/

typedef unsigned long OSlong;
typedef unsigned short OSshort;
typedef unsigned char OSchar;

/*				Intercard Communications Pointers		*/

struct	gCAP
{
	OSlong	iMagic;					/*	Magic Number	*/
	struct ca_Rec	*iPointer;		/*	CA Pointer		*/
	OSlong	iCksum;					/*	Checksum		*/
};

#ifndef __cplusplus
typedef struct gCAP gCAP;
#endif

/*			gCommon - A/ROSE common data area	*/


struct	gCommon		/*	Located at 0x400	*/
{
	OSshort	gRelease;			/*	release and version number					*/
	OSchar	gProcessor;			/*	Type of processor							*/
	OSchar	gCardRun;			/*	Set zero by download, non-zero by O/S		*/
	OSshort	gBoardID;			/*	Board id of card							*/
	OSlong	gTID;				/*	Current Task ID								*/
	OSchar	gDebugOn;			/*	non-zero if debugger running				*/
	OSchar	gMajorFlag;			/*	major processing flag						*/
	OSlong	gInitA5;			/*	Initial A5									*/
	OSlong	gBuffList;			/*	Pointer to memory buffer list				*/
	OSlong	gSlotAdd;			/*	slot address								*/
	OSlong	gSlotNum;			/*	slot number (<< 24)							*/
	OSlong	gTimeBase;			/*	load time of card (seconds since 1/1/1904)	*/
	OSlong	gMajorTick;			/*	major Tick counter							*/
	struct	gCAP	gCAPAddr;	/*	Communications Area Pointers				*/
	struct mMessage	*gMsgFree;	/*	message free list							*/
	OSlong	gUnique;			/*	Unique message ID							*/
	void	(*gTickChain) ();	/*	tick Process Chain							*/
	void	(*gIdleChain) ();	/*	idle task chain								*/
	struct	pTaskSave *gCurrTask;/*	current task pointer						*/
	OSlong	gIdleLoop;			/*	idle loop counter							*/
	struct	tTaskList *gTaskTable;/*	Pointer to task table					*/
	OSlong	gError;				/*	Error number								*/
	OSlong	gTimeout;			/*	timeout queue								*/
	struct	sPriority *gPriTable;/*	priority table pointer						*/
	struct	sPriority *gPriList;/*	priority task list							*/
	void	(*gUnregTask) ();	/*	name manager unregister routine address		*/
	OSlong	gMsgFlag;			/*	Message buffer flag							*/
	char 	*gFwaMess;			/*	fwa of message area							*/
	char	*gLwaMess;			/*	lwa of message area							*/
	char	*gInitPC;			/*	initial start address						*/
	char	*gFwaCode;			/*	fwa of initial downloaded code				*/
	char	*gLwaCode;			/*	lwa of initial downloaded code				*/
	OSlong	gMinorTick;			/*	minor tick counter							*/
	char	*gDebugTemp;		/*	Debugger pointer 							*/
	char	*gDebugCom;			/*	Debugger communication area					*/
	OSshort	gMinPerMaj;			/*	minor Ticks per Major Tick					*/
	OSshort	gTickPerSec;		/*	number of Major Ticks per Second			*/
	OSshort	gMajorDefer;		/*	major Ticks Deferred						*/
	OSshort	gMajorSkip;			/*	major Ticks Skipped							*/
	OSshort	gPageLatch;			/*	Page Latch value							*/
	tid_type	gNameTask;		/*	Name TID									*/
	tid_type	gIccTask;		/*	ICC TID										*/
	tid_type	gTraceTask;		/*	Trace TID									*/
	tid_type	gTimerTask;		/*	Timer TID									*/
	OSshort	gMsgBucket;			/*	message bucket count						*/
	OSchar	gTRQFlag;			/* 	true if time/task receive queue interlocked	*/
	OSchar	gBLFlag;			/*	set true if memory buffer list manipulated	*/
	OSshort	FreeMsgCount;		/* Number of free message buffers				*/
	OSlong	gTracePtr;			/*	Address of Trace Buffer Pointers			*/
	tid_type	gIMMTask;		/*	IMM TID	(does not need to be on this card)	*/
	void	(*gIMMHandler) ();	/*	IMM GW Handler routine						*/
	OSshort	gCPUInfo[4];		/*	Slot Manager CPU info for card				*/
	OSshort	gNetInfo[4];		/*	Slot Manager Netowkr info for card			*/
	void	(*gCardInit0) ();	/*	Card dependend initialization routine		*/
	void	(*gCardInit1) ();	/*	Card dependend initialization routine		*/
	void	(*gCardInit2) ();	/*	Card dependend initialization routine		*/
	struct ca_Rec	*gMainICCM;	/*	NuBus address of Main Board ICCM data area	*/
	unsigned long	gAddrBias;	/*	Address bias used for PC and A5				*/
	void	(*gHostInt) ();		/*	Host NMRQ interrupt routine					*/
	void	(*gClrInt) ();		/*	Clear inter-card IOP interrupt routine		*/
	OSlong	gClrVector;			/*	Clear interrupt routine auto vector address	*/
	struct IR_REC	*gIntRecord;/*	Inter-card interrupt record					*/
	OSshort	gTimerSR;			/*	SR to use to disable timer interrupts		*/
	OSshort	gTimeJMP;			/*	JMP word (0x04EF9) for jump to timer routine*/
	void	(*gTimeINTAddr) ();	/*	Time Int common processing routine address	*/
								/*	JMP to this address to enter common code	*/
	struct mMessage	*gSentMQH;	/*	Sent Message Q head							*/
	struct mMessage	*gSentMQT;	/*	Sent Message Q tail							*/
	unsigned long	gMemCnt;	/* 	Used is access is local						*/
	struct	MemMap *gMemMap;	/*	Local card memory map						*/
	unsigned long	gMemChk;	/*	Used is access is local						*/
	struct ca_Rec	*gLocIMM;	/*	Local address of ICCM area					*/
	void	(*gPWFChain) ();	/*	Power fail task chain						*/
	void	*gNameTable;		/*  Name table pointer							*/
	void	*gGlobalArea;		/*  Global area pointer when A/ROSE is downloaded */
	unsigned long	gTimeCorrection;	/* Time correction value				*/
	void	(*gICCRtn) ();		/*	ICCM Routine to process inter-card messages	*/
	char	filler[0x540-0x518];/*	Reserved - is zeroed by A/ROSE				*/
	short	gCardMask;			/* Mask of slots capable of running A/ROSE		*/
};

#ifndef __cplusplus
typedef struct gCommon gCommon;
#endif


/*			sPriority - Scheduling Priority Table	*/

struct	sPriority
{
	struct	sPriority	*sNext;		/*	Next Priority								*/
	struct	pTaskSave	*sNextTask;	/*	Points to next unblocked task in this ring	*/
	struct	pTaskSave	*sLastTask;	/*	Points to last unblocked task in this ring	*/
	short				sCount;		/*	Number of tasks in this priority ring		*/
};

#ifndef __cplusplus
typedef struct sPriority sPriority;
#endif

/*			bMemory - Buffer Memory Structure	*/


struct	bMemory
{
	struct	bMemory *bNext;			/*	Next block pointer							*/
	OSlong	bSize;					/*	Size of block								*/
};

#ifndef __cplusplus
typedef struct bMemory bMemory;
#endif

struct	tTaskList
{
	struct	pTaskSave	*tTaskEntry [cMaxTask]; /* One entry per Task				*/
};

#ifndef __cplusplus
typedef struct tTaskList tTaskList;
#endif

#ifdef __safe_link
extern "C" {
#endif
extern	struct gCommon	*GetgCommon();
#ifdef __safe_link
}
#endif

/*	Jump Table indices - to be used with SetJumpEntry()								*/

#define	ePostRTE			0	
#define	eFreeMem			1		
#define	eFreeMsg			2		
#define	eGetMem				3		
#define	eGetMsg				4		
#define	eReceive			5		
#define	eReschedule			6	
#define	eSend				7		
#define	eSpl				8		
#define	eStartTask			9	
#define	eStopTask			10	
#define	eBlockMove			11
#define	eBadCopyNuBus		12
#define	eGetBSize			13
#define	eGetCard			14
#define	eGetETick			15
#define	eGetgCommon			16
#define	eGetHeap			17	
#define	eGetStParms			18
#define	eGetTCB				19
#define	eGetTickPS			20
#define	eGetTID				21
#define	eGetICCTID			22
#define	eGetNameTID			23
#define	eGetTimerTID		24
#define	eGetTraceTID		25
#define	eGetUCount			26
#define	eICCReg				27
#define	eIncUCount			28
#define	eNameReg			29
#define	eTimerReg			30
#define	eTraceReg			31
#define	eLookup_Task		32
#define	eRegister_Task		33	
#define	eMapNuBus			34
#define	eToNuBus			35
#define	eIsLocal			36
#define	eSwapTID			37
#define	eIsTID				38
#define	eTLInitTimer		39
#define	eTLStartTimer		40
#define	eTLCancelTimer		41
#define	eTLActiveTimer		42
#define	eTLReceive			43
#define	eAROSESECS2DATE		44
#define	eAROSEDATE2SECS		45
#define	eAROSEGETDATETIME	46
#define	eIMMReg				47
#define	eGetIMMTID			48
#define	eNetCopy			49
#define	eNet_Register_Task	50
#define	eCountFreeMem		51
#define	eCountMaxMem		52
#define	eSuperCall			53
#define	eGetTIDIMM			54
#define	eNetLookup			55
#define	eOpenSection		56
#define	eCloseSection		57
#define	eResetPageLatch		58
#define	eFreeMsgCount		59
#define	eLockRealArea		60
#define	eUnlockRealArea		61
#define	eIMMHReg			62
#define eUnregister_Name	63
#define eSetupBusErrorHandler	64
#define eSetupPowerFail		65

#define	eLastEntry			65			/* Set to last entry index in table */

#ifdef __safe_link
extern "C" {
#endif

extern void SetJumpEntry();

#ifdef __safe_link
}
#endif
/*
	Debug area (starts at 0x600)
*/

struct cDebugArea {
	long D_Registers[8], A_Registers[8];
	short StatusRegister;
	long ProgramCounter, UserStackPtr;
	char BreakFlag, CommandCode;
	short SavedSR, Reserved;
	long TrapNumber, MemoryAddress, MemoryValue;
	char MemorySize, CommandStatus, Initialcrashflg;
};
#ifndef __cplusplus
typedef struct cDebugArea cDebugArea;
#endif

#define gCommonArea ((struct gCommon *)0x400)
#define debug ((struct cDebugArea *)0x600)

#endif

