/****************************************************************************/
/*																			*/
/*		iccmDefs.h - Definitions for inter-card communication				*/
/*																			*/
/*		Richard C. Sewill	01/05/88.										*/
/*																			*/
/*		Copyright © 1987-93,  Apple Computer, Inc.  All rights reserved.	*/
/*																			*/
/****************************************************************************/

#ifndef						_iccmDefs_defined_
#define	_iccmDefs_defined_

#include	"arose.h"
#include	"os.h"

/*	Symbol definitions.		*/

#define	ic_FVal			0x1CCA1943	/* Value of icca flag									*/

#define	ic_SlotMax		16			/* Maximum number of slots								*/

#define	ic_RtnSize		16			/* Size of Interrupt code for causing interrupt in bytes*/

#define	ic_Rdy			8			/* Full slot now ready									*/

#define	ic_BadReplyArea	32<<8		/* mStatus for bad GetCards request						*/

#define	ic_TMOValue		3			/* Timeout Delay in seconds before declaring card down	*/

/*	Structure definitions.	*/


/*	Communication Area Pointer Record.	*/

struct	cap_Rec	
{
	long	Flag;			/* Holds icca magic number (ic_FVal)	*/
	long	CaPtr;			/* Holds pointer to icca				*/
	long	CkSum;			/* Holds cap_Rec checksum				*/
};

/*	Communication Area Record.	*/

struct	ca_Rec
{
	long	Flag;				/* Magic constant										*/
	char	Format;				/* Format number of this communications area 			*/
	char	gDebugOn;			/* Non-zero if debugger running							*/
	char	IFlag;				/* Input flag, set if one or more IFlags set			*/
	char	IntFlg;				/* < 0 if cannot handle interrupts						*/
								/* = 0 if can handle interrupts and host can handle interrupts */
								/* > 0 if can handle interrupts but host not ready for them yet */
	char	IFlags[ic_SlotMax];	/* Input flags (set by sender, cleared by receiver)		*/
	long	Addrs[ic_SlotMax];	/* Addresses of slot's comm. areas						*/
	mMessage	*Ptrs[ic_SlotMax];	/* Pointers to receive buffers							*/
	long	QSCount;			/* Quick scan count										*/
	struct	IR_REC	*IntPtr;	/* Pointer to interrupt routines (structure TBD)		*/
	tid_type	NameMgr;		/* TID of name manager on this card						*/
	tid_type	IMMTID;			/* IMM Handler TID										*/
	unsigned long	MapCnt;		/* Address Map counter - incremented each time address 	*/
								/* map is changed.  Must be non-zero if address map is 	*/
								/* in use; zero otherwise								*/
	struct	AddrMap	*MapPtr;	/* Pointer to address map to be used for 				*/
								/* virtual to real address conversions					*/
	unsigned long	MapChk;		/* Contains the same value as MapCnt when the address 	*/
								/* map is NOT being manipulated.  Things walking the 	*/
								/* address map must check MapChk after fetching each 	*/
								/* link and after obtaining entry information to 		*/
								/* determine if the link/information is still valid 	*/
								/* (MapChk unchanged)									*/
	unsigned longAccCnt;		/* Access Map counter - incremented each time access 	*/
								/* map is changed.  Must be non-zero if access map is 	*/
								/* in use; zero otherwise								*/
	struct	AccList	*AccPtr;	/* Pointer to security  access map						*/
	unsigned long	AccChk;		/* Contains the same value as AccCnt when the access 	*/
								/* map is NOT being manipulated.  Things walking the 	*/
								/* access map must check AccChk after fetching each 	*/
								/* link and after obtaining entry information to 		*/
								/* determine if the link/information is still valid 	*/
								/* (AccChk unchanged)									*/
	unsigned long	Filler[17];	/* Reserved - Must be zero								*/

};

/*	Interrupt routine table structure */

#define	IR_Shift	6	/* The Interrupt routinetables are 64 bytes large */
#define	IR_SlotBias	8	/* Our Interrupt tables are biased by 8, only space for slots 8-$f */
#define	IR_RtnShft	4				/* Power of 2 Size of Interrupt routines	*/
#define	IR_RtnSize	1<<IR_RtnShft	/* Interrupt routines are each 16 bytes large */
struct	IR_REC
{
	OSlong	SIntPtr;				/* Set Interrupt routine pointer */
	OSchar	SIntRtn[IR_RtnSize];	/* Set Interrupt routine code */
	OSlong	CIntPtr;				/* Clear Interrupt routine pointer */
	OSchar	CIntRtn[IR_RtnSize];	/* Clear Interrupt routine code */
};

#endif

/*	End of iccmDefs.h.		*/

