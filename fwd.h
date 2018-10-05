/****************************************************************************/
/*																			*/
/*				fwd.h -  ADSP forwarder.									*/
/*																			*/
/*						Richard W. Mincher.		08/20/87					*/
/*																			*/
/*			Copyright © 1987-88,  Apple Computer, Inc.  All rights reserved.*/
/*																			*/
/****************************************************************************/
/*	Misc. Constants				*/

#include	"os.h"

#define	DATA_QUEUE			2200
#define	DATA_BUFFER			2100
#define	ECHO_DELTA			30		/*	Number of seconds between ECHO's	*/

/*	Message Codes				*/

#define	MC_OPENSERVER		0x1000		/*	Open Server				*/
#define	MC_CLOSESERVER		0x1002		/*	Close Server			*/
#define	MC_CLOSECONNECT		0x1004		/*	Connection Failed		*/
#define	MC_READDATA			0x1006		/*	read data (svr->task)	*/
#define	MC_SENDDATA			0x1008		/*	write data(task->svr)	*/
#define	MC_HITHERE			0x100A		/*	Identify Forwarder		*/
#define	MC_WHOAREYOU		0x2000		/*	Who Are You?			*/
#define	MC_ECHO				0x2002		/*	Echo back test			*/

/*	Error messages				*/

#define	FWE_NoError			0x0000	/*	No error							*/
#define	FWE_DupServer		0x0001	/*	Duplicate Server					*/
#define	FWE_CreateServer	0x0002	/*	Coundn't Create Server Block		*/
#define	FWE_NoServer		0x0003	/*	No error							*/
#define	FWE_State			0x0004	/*	No error							*/
#define	FWE_Write			0x0005	/*	No error							*/
#define	FWE_NoConnect		0x0006	/*	No error							*/
#define	FWE_Overflow		0x0007	/*	No error							*/
#define	FWE_NoSMemory		0x0008	/*	No error							*/
#define	FWE_NoSListen		0x0009	/*	No error							*/
#define	FWE_NoRegister		0x000A	/*	No error							*/

/*	Connection Status bits		*/

#define	CST_Read		0x0001		/*	Read pending						*/
#define	CST_Write		0x0002		/*	Write pending						*/
#define	CST_Closing		0x2000		/*	Notify Pending						*/
#define	CST_Notify		0x4000		/*	Notify Pending						*/
#define	CST_Memory		0x8000		/*	Memory complete						*/

/*	Connection States		*/


/*	Server Status bits		*/

#define	SST_Memory	0x8000			/*	Memory complete						*/
#define	SST_Closing	0x4000			/*	Close Pending						*/


/*	Server States			*/

#define	SSTATE_Init		0x0000		/*	Initial state						*/
#define	SSTATE_Create	0x0001		/*	listener CCB creating				*/
#define	SSTATE_Register	0x0002		/*	Listener registering				*/
#define	SSTATE_Listen	0x0003		/*	Listener listening					*/
#define	SSTATE_NoListen	0x0004		/*	Listener canceling					*/
#define	SSTATE_Unresist	0x0005		/*	Unregistering						*/

/*	Server Structure		*/

typedef	struct	Server
{
	struct	Server	*next;			/*	Next Server							*/
	NBPparms		*nPBPtr;		/*	NBP parameter block pointer			*/
	NamesTableEntry	*nte;			/*	Names Table Entry					*/
	DSPPBPtr		sPBPtr;			/*	Server Param Block pointer			*/
	TPCCB			lcb;			/*	Listener Control Block Pointer		*/
	DSPPBPtr		lPBPtr;			/*	Listener Param Block Pointer		*/
	struct	Connect	*connPtr;		/*	Connection pointer					*/
	long			timer;			/*	Watchdog timer value				*/
	short			lRefNum;		/*	Listener Reference Number			*/
	tid_type		tid;			/*	Process ID							*/
	short			status;			/*	Server Status						*/
	short			state;			/*	Server State						*/
	short			socket;			/*	Socket ID							*/
	struct mMessage	*msg;			/*	Mr.Dos Message						*/
	Boolean			disconnect;		/*  Disconnect flag						*/
} Server, *ServerPtr;

/*	Connection Structure		*/

typedef	struct	Connect
{
	struct	Connect	*next;				/*	Next Connection					*/
	struct	Server	*serv;				/*	Server Pointer					*/
	DSPPBPtr		cPBPtr;				/*	Connection Param Block Pointer	*/
	TPCCB			ccb;				/*	Connection Control Block Pointer*/
	DSPPBPtr		rPBPtr;				/*	Read Param Block Pointer		*/
	DSPPBPtr		wPBPtr;				/*	Write Param Block Pointer		*/
	struct mMessage	*wMsg;				/*	Write message reply				*/
	char			*sendQ;				/*	Send Queue						*/
	char			*recvQ;				/*	Receive Queue					*/
	char			*attnQ;				/*	Attention Queue					*/
	char			*readBuf;			/*	Read buffer						*/
	char			*sendBuf;			/*	Send buffer						*/
	short			cRefNum;			/*	CCB reference number			*/
	short			status;				/*	Connection Status				*/
	short			state;				/*	Connection State				*/
} Connect, *ConnectPtr;

/*	Appletalk Transition queue element	*/

typedef struct
	{
	long		fQLink;				/* For the queue */
	short		fQType;				/* Why not? */
	long		fCallAddr;			/* Function Pointer for us */
	}
ATalkQEntry;

/*	Global Data Structure		*/

typedef	struct	GlobalData
{
	ServerPtr		svrList;		/*	Server List							*/
	ServerPtr		FreeSrvr;		/*	Free Server							*/
	ConnectPtr		FreeConn;		/*	Free Server							*/
	short			QFlag;			/*	Queue flag							*/
	short			dspRef;			/*	DSP Reference Number				*/
	char			SysTask;		/*	AccRun Flag							*/
	char			ScanFlag;		/*	AccRun Flag							*/
	short			MaxFreeSvr;		/*	Maximum number of free servers		*/
	short			MaxFreeCnn;		/*	Maximum number of free connections	*/
	struct mMessage	*MRDOSmsgs;		/*	MR-DOS messages from completion rtn	*/
	char			workFlag;		/*	Non-zero if work to do				*/
	char			ATClosed;		/*	Non-zero if at has been closed		*/
	ATalkQEntry		atQE;			/*	AT Queue Entry						*/
} GlobalData, *GlobalDataPtr;

#define TRUE 0xff
#define FALSE 0x00