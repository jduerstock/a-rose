/*
 *	timerlibrary.h - Definitions for use with the timerlibrary.
 *
 *	Copyright © 1993,  Apple Computer, Inc.  All rights reserved.
 */

#ifndef						_timerlibrary_defined_
#define	_timerlibrary_defined_

#include	"os.h"

struct Tmem
{
	long			NumberMessages;
	unsigned long	time_to_wait;
	mMessage		*head;
	mMessage		dummy;
	long			no_mess_count;
};

typedef struct Tmem TOPB;

#ifdef __safe_link
extern "C" {
#endif

extern TOPB			*TLInitTimer ();

extern char			TLStartTimer (TOPB*, mMessage*);

extern long			TLActiveTimer (TOPB*, unsigned long);

extern mMessage		*TLCancelTimer (TOPB*, unsigned long);

extern mMessage		*TLReceive (TOPB*, unsigned long, tid_type, unsigned short);

#ifdef __safe_link
}
#endif

#endif