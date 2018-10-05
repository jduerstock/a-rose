/********************************************************************************/
/*																				*/
/*						diags.h - - Diagnostic constants.						*/
/*																				*/
/*			Richard C. Sewill.								11/23/87.			*/
/*																				*/
/*		Copyright © 1987-88, Apple Computer, Inc. 		All rights reserved.	*/
/*																				*/
/********************************************************************************/

/* Request codes */

#ifndef						_diags_defined_
#define	_diags_defined_

#define	finish				500			/* stop the task								*/	
#define	getmem				502			/* get memory on card							*/
#define	freemem				504			/* release memory on card						*/			
#define	test_and_set		506			/* Perform test and set test					*/				
#define	RAM_test			508			/* Perform RAM test								*/
#define	ROM_test			510			/* Perform ROM test								*/
#define	test_set_interrupt	512			/* Perform test, set, and interrupt				*/
#define	init_test_set_bfr	514			/* Initialize test and set buffer				*/
/* Error Constants */

#define	DIE_NOERR			0		/*	No error												*/
#define	DIE_ABORT			1		/*	Request aborted											*/
#define	DIE_BADREQ			2		/*	Bad request												*/
#define	DIE_RAMFAIL			3		/*	RAM test failed											*/
#define	DIE_ROMFAIL			4		/*	ROM test failed											*/
#define	DIE_TASFAIL			5		/*	Test and Set buffer check failed						*/
#define	DIE_BUFSMALL		6		/*	Test and Set buffer too small							*/
#define	DIE_BUFALIGN		7		/*	Test and Set buffer not word aligned					*/
#define	DIE_BUFADDR			8		/*	Test and Set buffer not local on initialization request	*/

#endif

