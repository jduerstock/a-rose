/*
 *			Common stuff.
 *			
 *	Copyright Apple Computer, Inc. 1987-88
 *	All rights reserved.
 *
 *  Added declarations for structure names to be friendly to C++
 */

#ifndef utiny
#define	utiny	unsigned char
#endif

#ifndef	boolean
#define	boolean	char
#endif

#ifndef	NULL
#define	NULL					0
#endif

#ifndef	_managers_defined_
#define	_managers_defined_

#include	"os.h"

/*			Common error codes - os defined (0<<8 - 19<<8)					*/

#define	OS_NO_ERRORS			(0<<8)	/* no errors - all is ok			*/
#define	OS_UNKNOWN_MESSAGE		(1<<8)	/* unknown message					*/

/*			Common message codes - os defined (2-99)						*/

#define	MC_STOP					2		/* clean up and stop task			*/

/*
 *			Name Manager related stuff.
 */


#define NM_Type_Size_Max		32		/* max chars in type name			*/
#define NM_Obj_Size_Max			32		/* max chars in object name			*/
#define	Machine_Visible			0		/* Register_task Machine visible flag	*/
#define	Locally_Visible			1		/* Register_Task locally visible flag	*/
#define	World_Visible			-1		/* Register_task World visible flag		*/
#define NM_WILDCARD				'='		/* wildcard character, matches all	*/
#define	NM_Max_Slot				16		/* maximum number of slots			*/
/*	
						Name Manager Message Codes - (MUST BE EVEN NUMBER) (100 - 121)
*/	

#define	NM_REG_TASK				100				/* register task 						*/
#define	NM_LOOKUP_PID			102				/* lookup process id 					*/
#define NM_LOOKUP_TID			NM_LOOKUP_PID	/* lookup task id 						*/
#define	NM_LOOKUP_NAME			104				/* lookup name 							*/
#define	NM_UNREG_TASK			106				/* unregister task 						*/
#define	NM_N_SLOT_REQ			108				/* notify task on slot down				*/
#define	NM_N_TASK_REQ			110				/* notify task on task stopped			*/
#define	NM_N_SLOT_CAN			112				/* cancel task notify on slot down		*/
#define	NM_N_TASK_CAN			114				/* cancel task notify on task stopped	*/
#define	NM_UNREG_NAME			116				/* unregister name						*/
#define	NM_NET_REG_TASK			118				/* Network register task 				*/
#define	NM_TRUNCATE_TABLES		120				/* Internal NM Msg - truncate tables	*/


/*
						Error Codes
*/

#define	NM_NO_ERRORS			OS_NO_ERRORS		/* no errors - all is ok			*/
#define NM_UNKNOWN_MESSAGE		OS_UNKNOWN_MESSAGE	/* unknown message					*/
#define	NM_LTID_PB_TOO_SMALL	(20<<8)				/* lookup tid parm block too small	*/
#define	NM_RT_PB_TOO_SMALL		(21<<8)				/* register task parm block to smal	*/
#define	NM_LN_PB_TOO_SMALL		(22<<8)				/* lookup name parm block too small	*/
#define	NM_RA_LTID_TOO_SMALL	(23<<8)				/* lookup tid return area too small	*/

#define	NM_RA_LNM_TOO_SMALL		NM_RA_LTID_TOO_SMALL

#define	NM_INVALID_NAME_SIZE	(24<<8)	/* invalid name size register task	*/ 
#define	NM_DUPLICATE_NAME		(25<<8)	/* name already registered			*/
#define	NM_ERR_NO_MEMORY		(26<<8)	/* no memory available for request	*/
#define	NM_RT_REMOTE_REG		(27<<8)	/* remote registration not allowed	*/
#define	NM_SLOT_NOT_UP			(28<<8)	/* notify-slot not up				*/
#define	NM_TASK_NOT_EXIST		(29<<8)	/* notify-local task does not exist	*/
#define	NM_NAME_NOT_REG			(30<<8)	/* notify-remote task does not exist*/
#define	NM_BAD_SLOT_NUMBER		(31<<8)	/* notify-bad slot number specified	*/
#define	NM_BAD_TASK_NUMBER		(32<<8)	/* notify-bad task number-not local	*/
#define	NM_NO_ENTRY_FOUND		(33<<8)	/* notify-no table entry found		*/
#define	NM_NAME_NOT_FOUND		(34<<8)	/* unregister name-name not found	*/
#define	NM_NOMEMAVAIL			(35<<8)	/* No memory available to process request */

/*
						structure definitions
*/

struct obj_rec							/* object name record				*/
{										/* DO NOT CHANGE THE ORDER			*/
	utiny	o_len;						/* length of object name 			*/
	char	o_name [NM_Obj_Size_Max];	/* maximum chars in object name		*/
};

#ifndef __cplusplus
typedef struct obj_rec obj_rec;
#endif

struct typ_rec							/* type name record					*/
{										/* DO NOT CHANGE THE ORDER			*/
	utiny	t_len;						/* length of object name 			*/
	char	t_name [NM_Type_Size_Max];	/* maximum chars in object name		*/
};

#ifndef __cplusplus
typedef struct typ_rec typ_rec;
#endif

struct pb_register_task					/* register name param block		*/
{
	struct 	obj_rec		rt_on;			/* object name						*/
	struct	typ_rec		rt_tn;			/* type name						*/
	char				rt_local_vis;	/* locally visible only flag		*/
};

#ifndef __cplusplus
typedef struct pb_register_task pb_register_task;
#endif

struct pb_unregister_name				/* unregister name param block		*/
{
	struct 	obj_rec		ut_on;			/* object name						*/
	struct	typ_rec		ut_tn;			/* type name						*/
};

#ifndef __cplusplus
typedef struct pb_unregister_name pb_unregister_name;
#endif

struct	ra_ltid							/* return area for lookup tid		*/
{
	struct	obj_rec		ra_on;			/* object name						*/
	struct	typ_rec		ra_tn;			/* type name						*/
	tid_type			ra_tid;			/* process id						*/
};

#ifndef __cplusplus
typedef struct ra_ltid ra_ltid;
#endif

struct	pb_lookup_tid					/* lookup process id parameter block	*/
{
	struct		obj_rec	ltid_on;		/* object name						*/
	struct		typ_rec	ltid_tn;		/* type name						*/
	unsigned	short	ltid_index;		/* index							*/
	unsigned	short	ltid_RAsize;	/* size of return area				*/
	struct		ra_ltid	ltid_ra [1];	/* return area		(OUTPUT)		*/
};

#ifndef __cplusplus
typedef struct pb_lookup_tid pb_lookup_tid;
#endif

struct	ra_lnm							/* return area for lookup name		*/
{
	struct	obj_rec		ra_on;			/* object name						*/
	struct	typ_rec		ra_tn;			/* type name						*/
};

#ifndef __cplusplus
typedef struct ra_lnm ra_lnm;
#endif

struct pb_lookup_name
{
	tid_type			lnm_tid;		/* process id						*/
	unsigned	short	lnm_index;		/* index		(INPUT/OUTPUT)		*/
	unsigned	short	lnm_RAsize;		/* size of return area				*/
	struct		ra_lnm	lnm_ra [1];		/* return area		(OUTPUT)		*/
};

#ifndef __cplusplus
typedef struct pb_lookup_name pb_lookup_name;
#endif

/*
 *				Time manager related stuff.
 */

/*				time manager message codes		(120 - 139)				*/

#define	TIMER_1_SHOT_REQUEST	120		/* one shot timer request		*/
#define	TIMER_1_SHOT_REPLY		121		/* one shot timer reply			*/

#define TIMER_PERIODIC_REQUEST	122		/* periodic time request		*/
#define TIMER_PERIODIC_REPLY	123		/* periodic time reply			*/

#define	TIMER_QUERY_REQUEST		124		/* timer query request			*/
#define	TIMER_QUERY_REPLY		125		/* timer query reply			*/

#define TIMER_CANCEL_REQUEST	126		/* timer cancel request			*/
#define	TIMER_CANCEL_REPLY		127		/* timer cancel reply			*/

/*				define error codes										*/

#define	TIMER_NO_ERRORS			OS_NO_ERRORS		/* no errors					*/
#define	TIMER_UNKNOWN_MESSAGE	OS_UNKNOWN_MESSAGE	/* unknown message				*/
#define	TIMER_CANCELLED			(40<<8)				/* timer already cancelled		*/		

/*
 *				Print manager related stuff  (140 - 149).
 */

#define	PRINT_ME		140				/* print the buffer							*/
#define	PRINT_READY		142				/* internal message do not use, PLEASE!!	*/
#define	PRINT_START		144				/* Continue printing of messages			*/
#define	PRINT_STOP		146				/* Stop printing messages - do not go away	*/

/*
 *				ICCM message codes (150 - 159).
 */

#define	IC_MAXCARDS		16				/* Maximum number of NuBus cards allowed	*/

#define	ICC_GETCARDS	150				/* Get list of active cards and their name	*/
										/* manager addresses.  mDataPtr points to	*/
										/* the response buffer of the form below.	*/
										/* mDataSize = sizeof (struct ra_GetCards)	*/
#define	ICC_GETIMMS		152				/* Get list of active cards and their IMM	*/
										/* manager addresses.  mDataPtr points to	*/
										/* the response buffer of the form below.	*/
										/* mDataSize = sizeof (struct ra_GetIMMs)	*/
#define ICC_DETACH		154				/* Detach card from others					*/
#define ICC_ATTACH		156				/* Attach card with others					*/
#define	ICC_INTCARD		1150			/* Enable/Disable intercard interrupts		*/

/*
 *				ICCM error codes.
 */

#define	IC_BAD_REPLY_AREA	(50<<8)


/*
 *				ICCM structure definitions.
 */

struct ra_GetCards						/* Format of reply to ICC_GETCARDS			*/
{
	tid_type	tid[IC_MAXCARDS];	/* < 0 means corr. card not present,			*/
									/* = 0 means card present - no name manager,	*/
									/* > 0 means address of name manager on card	*/
									/*     may be used in mTo field of a message	*/
};

#ifndef __cplusplus
typedef struct ra_GetCards ra_GetCards;
#endif

struct ra_GetIMMs						/* Format of reply to ICC_GETIMMS			*/
{
	tid_type	tid[IC_MAXCARDS];	/* < 0 means corr. card not present,			*/
									/* = 0 means card present - no IMM manager,		*/
									/* > 0 means address of IMM manager on card		*/
									/*     may be used in mTo field of a message	*/
};

#ifndef __cplusplus
typedef struct ra_GetIMMs ra_GetIMMs;
#endif


/*
 *				Remote System message codes (160 - 199).
 */

#define RSM_FreeMem		160			/* Free Memory System Call						*/
#define RSM_GetMem		164			/* GetMem System Call							*/
#define RSM_StartTask	168			/* StartTask System Call						*/
#define RSM_StopTask	170			/* StopTask System Call							*/
#define RSM_MemoryInfo	180			/* CountFreeMem/CountMaxMem Calls				*/

#define RSM_FreeMsg		162			/* Free Message System Call	(NOT IMPLEMENTED)	*/
#define RSM_GetMsg		166			/* GetMsg System Call  (NOT IMPLEMENTED)		*/
#define RSM_Receive		172			/* Receive System Call (NOT IMPLEMENTED)		*/
#define RSM_Reschedule	174			/* Reschedule System Call (NOT IMPLEMENTED)		*/
#define RSM_Send		176			/* Send System Call (NOT IMPLEMENTED)			*/
#define RSM_SPL			178			/* SPL System Call (NOT IMPLEMENTED)			*/

/*
 *				Remote System Manager Error Codes
 */
 
#define RSE_NO_ERRORS			OS_NO_ERRORS
#define RSE_UNKNOWN_MESSAGE 	OS_UNKNOWN_MESSAGE
#define RSE_NOT_MEM			(60 << 8)	/* error - not a memory region				*/
#define RSE_NOT_MSG			(61 << 8)	/* error - not a message region				*/
#define RSE_PB_BAD_SIZE		(62 << 8)	/* error - parm block not correct size		*/
#define RSE_NO_PB			(63 << 8)	/* error - no parameter block				*/
#define RSE_CODESEGMENT		(64 << 8)	/* error - no code segment 					*/
#define RSE_DATASEGMENT		(65 << 8)	/* error - no data segment					*/
#define RSE_STARTPARMSEG	(66 << 8)	/* error - no start parameter segment		*/
#define RSE_PC_BAD			(67 << 8)	/* error - PC out of range					*/
#define RSE_No_TCB			(68 << 8)	/* error - could not allocate TCB			*/

/*
 *				Trace Manager message codes (200 - 219).
 */

#define TM_TRACE			200		/* Trace Message */			
#define TM_TRACE_ON			202		/* Turn Tracing On */		
#define TM_TRACE_OFF		204		/* Turn Tracing Off */		

/*
 *				Trace Manager Error Codes
 */
 
#define TME_UNKNOWN_MESSAGE	OS_UNKNOWN_MESSAGE	

/*
 *				Inter-Machine Manager message codes (220 - 239)
 */
 /* cbo - Took out most of IMM definitions. The ones that are left are needed
 		for inter-slot NetCopy's that need help from the motherboard. This
		might be added to if IMM (ROSA) ever becomes a real manager.
 */

#define IMM_NetCopy			220		/* Perform NetCopy Operation 	*/			

/*
 *				Inter-Machine Manager Error Codes
 */

#define	IMM_REMOTETIDBAD	(86 << 8)	/* Remote TID is bad, i.e., it is not mapped.		*/ 
#define	IMM_NoMsgAvail		(87 << 8)	/* No message buffer available						*/

#endif	_managers_defined

/*	End of managers.h */
