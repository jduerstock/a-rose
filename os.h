/*
 *	os.h - Definitions for use with user application files.
 *
 *	Copyright © 1987-88,  Apple Computer, Inc.  All rights reserved.
 */

#ifndef						_os_defined_
#define	_os_defined_

#define	OS_SLICE_MODE	0		/* scheduling is done using time slicing	*/
#define	OS_BLOCK_MODE	1		/* scheduling is done when task blocks		*/
#define	OS_SLICE_IMMED	2		/* scheduling is done with slice mode - no CPU switch */
#define	OS_BLOCK_IMMED	3		/* scheduling is done when task blocks - no CPU switch	*/
#define	OS_RTN_MODE		4		/* current scheduling mode is returned		*/
#define	OS_RTN_IMMED	6		/* current scheduling mode is returned - no CPU switch	*/


#define	OS_MATCH_ALL	0		/* on receive match anything				*/
#define	OS_MATCH_NONE	(-1)	/* message code that does not exist			*/

#define	OS_NO_TIMEOUT	0		/* receive waits forever for message		*/

#define STE_NO_ERRORS 	0				/* StartTask - No error  			*/
#define	STE_NO_TCB		0x8001			/* StartTask - No TCB allocated		*/
#define	erLockFailed	0x8002			/* LockRealArea - failed			*/
#define	erUnlockFailed	0x8003			/* UnlockRealArea - failed 			*/

/*	Apple IPC driver error codes */

#define	NoQueueErr		-64		/* Error code for no more queues			*/
#define	QueueBusy		-65		/* Receive already outstanding on a queue	*/

/*	Structures	*/

typedef long	tid_type;

struct mMessage
{
	struct	mMessage	*mNext;
	long				mId;
	short				mCode;
	short				mStatus;
	unsigned	short	mPriority;
	tid_type			mFrom;
	tid_type			mTo;
	unsigned	long	mSData [3];
	unsigned	long	mOData [3];
	long				mDataSize;		/* Size of data buffer in bytes. set to negative */
										/* size of buffer if buffer is shared*/
										/* between tasks. eg. Buffer cannot be copied */
	char				*mDataPtr;
};

#ifndef __cplusplus
typedef struct mMessage mMessage;
#endif

typedef struct mMessage AROSEmessage;

#ifndef __UFailure__
#ifndef __EVENTS__
typedef	struct mMessage message;
#endif
#endif

/*
 *				Parameter Block Definition for StartTask
 */
  
struct ST_Registers
{
	long	D_Registers [8];		/* D0 - D7 										*/
	long	A_Registers [8];		/* A0 - A7  Note: A7 not used					*/
	long	PC;						/* Program Counter								*/
};

#ifndef __cplusplus
typedef struct ST_Registers ST_Registers;
#endif

struct ST_PB
{
	char	*CodeSegment;			/* memory region on card for code				*/
	char	*DataSegment;			/* memory region on card for global data		*/
	char	*StartParmSegment;		/* memory region on card for start parameters	*/
	struct	ST_Registers InitRegs;	/* initial register set for starting task		*/
	long	stack;					/* initial stack size (in bytes)				*/
	long	heap;					/* initial heap size (in bytes)					*/
	short	return_code;			/* error code if task not started (Tid = 0)		*/
	unsigned char priority;			/* priority of task (in bytes)					*/
	tid_type	ParentTID;			/* TID of Parent on Network/Host				*/
};

#ifndef __cplusplus
typedef struct ST_PB ST_PB;
#endif

/*			pTaskSave - Task Control Block (TCB)		*/


struct	pTaskSave
{
	struct	pTaskSave *pNextTask;	/*	Next Task (Priority Queue)					*/
	struct	pTaskSave *pNextTime;	/*	Next Task (Timeout Queue)					*/
	char	*pStackBuf;				/*	Stack Buffer Pointer						*/
	char	*pHeapBuf;				/*	Heap Buffer Pointer							*/
	unsigned long	pPcSave;		/*	Program Counter								*/
	char	*pSpSave;				/*	Stack Pointer								*/
	char	*pCodeSeg;				/*	code segment or null						*/
	char	*pDataSeg;				/*	data segment (globals) or null				*/
	char	*pStartParm;			/*	start parameter segment or null				*/
	tid_type	pParentTID;			/* TID of Parent on Network/Host				*/
	unsigned short	pSrSave;		/*	Status Register								*/
	unsigned short	pPageLatch;		/*	Page Latch									*/
	unsigned char	pPriority;		/*	Priority									*/
	unsigned char	pRcvFlag;		/*	Non-zero if Receive, Negative if match all	*/
	unsigned short	pTID;			/*	Process ID									*/
	struct	mMessage *pQHead;		/*	Message Q Head								*/
	struct	mMessage *pQTail;		/*	Message Q Tail								*/
	unsigned long	pQTimeout;		/*	Message Q Blocking Timeout					*/
	unsigned long	pQMsgID;		/*	Message Q Message ID Block					*/
	unsigned long	pQMsgFrom;		/*	Message Q From Block						*/
	unsigned short	pQMsgCode;		/*	Message Q Code Block						*/
	unsigned char	pTMQFlag;		/*	Non-zero if Receive & in timeout queue		*/
	unsigned char	pBlockMode;		/*	Non-zero if Block mode						*/
	void	*pStartAddr;			/*  48 - Start address of the dynamic task		*/
	void	*pGlobalArea;			/*  4C - Global area start address				*/
	struct sPriority *pPriListPtr;	/*	50 - gPriList entry this task is part of	*/
};

#ifndef __cplusplus
typedef struct pTaskSave pTaskSave;
#endif

/*	Address Map List - contains virtual to real address conversions	*/

struct addressareas			/* individual real address/length area	*/
{
	void 		*address;	/* Physical address of memory area */
	unsigned long length;	/* Length of memory area */
};

#ifndef __cplusplus
typedef struct addressareas addressareas;
#endif

struct	AddrMap
{
	struct AddrMap	*vNext;		/* Virtual address of next address map list or zero 	*/
	struct AddrMap	*rNext;		/* Real address of next address map list or zero 		*/
	tid_type		tid;		/* TID associated with this virtual address				*/
	unsigned short	flags;		/* Reserved for now - must be zero						*/
	unsigned short	usage;		/* Usage count - non-zero means entry in use			*/
	unsigned long	MapSize;	/* Length of AddrMap entry								*/
	void			*vAddress;	/* Virtual address										*/
	unsigned long	vlength;	/* Length associated with virtual address	 			*/
	struct addressareas	areas[1];/* physical address/length pairs						*/
};

#ifndef __cplusplus
typedef struct AddrMap AddrMap;
#endif

struct AROSEDateTimeRec {
    short year;
    short month;
    short day;
    short hour;
    short minute;
    short second;
    short dayOfWeek;
};

#ifndef __cplusplus
typedef struct AROSEDateTimeRec AROSEDateTimeRec;
#endif

/*	Function declarations  */

#ifndef applec   MPW 2.0 C

/*  A/ROSE Primitives  */

#ifndef __MEMORY__
#define FreeMem		AROSEFreeMem
#define GetMem		AROSEGetMem
#define BlockMove	AROSEBlockMove
#endif

#ifdef __safe_link
extern "C" {
#endif

extern	void			AROSEFreeMem();
extern	void			FreeMsg();
extern	char			*AROSEGetMem();
extern	struct mMessage	*GetMsg();
extern	struct mMessage	*Receive();
extern	short			Reschedule();
extern	void			Send();
extern	short			Spl();
extern	tid_type		StartTask();
extern	void			StopTask();

/*  A/ROSE Utilities  */

extern	void			AROSEBlockMove();
pascal void				AROSEDate2Secs(Date, secs)
						AROSEDateTimeRec *Date;
						unsigned long *secs;
						extern;
extern	unsigned long	GetBSize();
extern	unsigned char	GetCard();
pascal void				AROSEGetDateTime(secs)
						unsigned long *secs;
						extern;
extern	unsigned long	GetETick();
extern	struct gCommon	*GetgCommon();
extern	char			*GetHeap();
extern	tid_type		GetICCTID();
extern	tid_type		GetIMMTID();
extern	tid_type		GetNameTID();
extern	char			*GetStParms();
extern	struct pTaskSave	*GetTCB();
extern	unsigned short	GetTickPS();
extern	tid_type		GetTID();
extern	tid_type		GetTimerTID();
extern	tid_type		GetTraceTID();
extern	unsigned char	GetUCount();
extern	unsigned char	IncUCount();
extern	short			IsLocal();
extern	tid_type		Lookup_Task();
extern	char			*MapNuBus();
extern	short			NetCopy();
extern	char			Net_Register_Task();
extern	char			Register_Task();
pascal void				AROSESecs2Date(secs, Date)
						unsigned long secs;
						AROSEDateTimeRec *Date;
						extern;
extern	void			SuperCall();
extern	void			SwapTID();
extern	char			*ToNuBus();
extern	void			TraceReg();

/*	motherboard support	*/

extern	tid_type		OpenQueue();
extern	void			CloseQueue();
extern	void			KillReceive();
extern	void			PushAIPC();

/*  VM support  */

extern	short			LockRealArea();
extern	short			UnlockRealArea();

/*	self-powered card support	*/

extern	void			SetupBusErrorHandler();
extern	void			SetupPowerFail();

#ifdef __safe_link
}
#endif

#else	MPW 3.0 C

/*  A/ROSE Primitives  */

#ifndef __MEMORY__
#define FreeMem		AROSEFreeMem
#define GetMem		AROSEGetMem
#define BlockMove	AROSEBlockMove
#endif

#ifdef __safe_link
extern "C" {
#endif

extern	void			AROSEFreeMem(char *);
extern	void			FreeMsg(struct mMessage *);
extern	char			*AROSEGetMem(long);
extern	struct mMessage	*GetMsg(void);
#ifndef __cplusplus
extern	struct mMessage	*Receive();
#else
extern	struct mMessage *Receive(unsigned long, tid_type, unsigned short, long, ...);
#endif
extern	short			Reschedule(short);
extern	void			Send(struct mMessage *);
extern	short			Spl(short);
extern	tid_type		StartTask(struct ST_PB *);
extern	void			StopTask(tid_type);

/*  A/ROSE Utilities  */

extern	void			AROSEBlockMove(void *, void *, long);
extern pascal void		AROSEDate2Secs(const AROSEDateTimeRec *,unsigned long *);
extern	unsigned long	GetBSize(char *);
extern	char			GetCard(void);
extern	pascal void		AROSEGetDateTime(unsigned long *);
extern	unsigned long	GetETick(void);
extern	struct gCommon	*GetgCommon(void);
extern	char			*GetHeap(void);
extern	tid_type		GetICCTID(void);
extern	tid_type		GetNameTID(void);
extern	char			*GetStParms(void);
extern	struct pTaskSave	*GetTCB(void);
extern	unsigned short	GetTickPS(void);
extern	tid_type		GetTID(void);
extern	tid_type		GetTimerTID(void);
extern	tid_type		GetTraceTID(void);
extern	unsigned char	GetUCount(char *);
extern	unsigned char	IncUCount(char *);
extern	short			IsLocal(char *);
extern	tid_type		Lookup_Task(char *, char *, tid_type, unsigned short *);
extern	char			*MapNuBus(char *);
extern	char			Net_Register_Task(char *, char *);
extern	short			NetCopy(tid_type, void *, tid_type, void *, unsigned long);
extern	char			Register_Task(char *, char *, short);
extern	pascal void		AROSESecs2Date(unsigned long, AROSEDateTimeRec *);
extern	void			SuperCall();
extern	void			SwapTID(struct mMessage *);
extern	char			*ToNuBus(char *);
extern	void			TraceReg(void);

/*	Motherboard support	*/

extern	tid_type		OpenQueue(void (*)());
extern	void			CloseQueue();
extern	void			KillReceive();
extern	void			PushAIPC();

/*	Self-powered card support	*/

extern	void			SetupBusErrorHandler(void);
extern	void			SetupPowerFail(void);

/*  VM support  */

extern	short			LockRealArea(void *, unsigned long, struct addressareas buffer[], unsigned long);
extern	short			UnlockRealArea(void *, unsigned long);
#ifdef __safe_link
}
#endif

#endif

#endif