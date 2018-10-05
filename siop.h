/************************************************************************/
/*																		*/
/*					siop.h - SIOP board definitions.					*/
/*																		*/
/*					Richard W. Mincher.		87/02/05.					*/
/*																		*/
/*		Copyright© 1987-88, Apple Computer, Inc.  All rights reserved.	*/
/*																		*/
/************************************************************************/
/*
 *	Steve K. Wang	Aug. 27th 87
 *	add ifdef statement around to support both AST & Apple MCP cards
 */

#ifndef						_siop_defined_
#define	_siop_defined_ 
 
/* 			Common constants		*/

#define	RAM_INCR	0x080000	/*	RAM length increment			*/
#define	DEBUGGER	0xf1000		/*	Debugger Starting Address		*/

/*			Soft Addresses			*/

#define		INIT_SP			0x000000	/*	Initial Stack Pointer		*/
#define		INIT_PC			0x000004	/*	Initial Program Counter		*/
#define		INIT_VERSION	0x000400	/*	Version level of Download	*/
#define		INIT_PROCESSOR	0x000402	/*	Processor type				*/
#define		INIT_BOARDID	0x000404	/*	Board id of card			*/
#define		INIT_A5			0x00040c	/*	Initial A5 Address			*/
#define		INIT_FREE		0x000410	/*	Initial FREE Address		*/
#define		INIT_SLOTAD		0x000414	/*	Initial slot NuBus address	*/
#define		INIT_SLOTNO		0x000418	/*	Initial slot number (0-F)	*/
#define		INIT_TIME		0x00041c	/*	Initial time (1/10 seconds)	*/
#define		INIT_CPUINFO	0x0004B0	/*	Slot Manager CPU info for card			*/
#define		INIT_NETINFO	0x0004B8	/*	Slot manager Netowrk info for card		*/
#define		INIT_CARDRTN0	0x0004C0	/*	Card dependent initialization routine	*/
#define		INIT_CARDRTN1	0x0004C4	/*	Card dependent initialization routine	*/
#define		INIT_CARDRTN2	0x0004C8	/*	Card dependent initialization routine	*/
#define		INIT_DBG		0x000600	/*	Debugger Data				*/
#define		INIT_LOAD		0x000800	/*	Initial load address 		*/

 
#ifndef	SIOPDEF
#define	SIOPDEF

/*		SCC Offset Addresses		*/

#define	AST_SCC_ONE		0x000000		/*	Offset of SCC #1			*/
#define	AST_SCC_TWO		0x004000		/*	Offset of SCC #2			*/

#define	AST_SCC_CHA_A	0x000004		/*	Offset of Channel A			*/
#define	AST_SCC_CHA_B	0x000000		/*	Offset of Channel B			*/

#define	AST_SCC_COMMAND	0x000000		/*	Offset of Command Register	*/
#define	AST_SCC_DATA	0x000002		/*	Offset of Data Register		*/

/*		Base Addresses		*/

#define	RAM_BASE	0x000000		/*	RAM base address			*/
#define	AST_SCC_BASE	0x0B0000		/*	SCC base address			*/
#define	AST_VIA_BASE	0x0C0000		/*	VIA base address			*/
#define	AST_NAP_BASE	0x0D0000		/*	NuBus Page Address Latch	*/
#define	AST_ROM_BASE	0x0F0000		/*	ROM base address			*/
#define	AST_NUBUS	0x800000		/*	NuBus access - normal		*/
#define	RMW_BASE	0xC00000		/*	NuBus access - RMW			*/



/*		VIA Addresses				*/

#define	VIA_IORB	0x000000	/*	I/O Register B					*/
#define	AST_VIA_IORA	0x000002	/*	I/O	Register A					*/
#define	AST_VIA_DDRB	0x000004	/*	Data Direction Register B		*/
#define	AST_VIA_DDRA	0x000006	/*	Data Direction Register A		*/
#define	VIA_T1CL	0x000008	/*	T1 Low-Order Latch / Counter	*/
#define	VIA_T1CH	0x00000A	/*	T1 High Order Counter			*/
#define	VIA_T1LL	0x00000C	/*	T1 Low-Order Latches			*/
#define	VIA_T1LH	0x00000E	/*	T1 High-Order Latches			*/
#define	VIA_T2CL	0x000010	/*	T2 Low-Order Latch / Counter	*/
#define	VIA_T2CH	0x000012	/*	T2 High-Order Counter			*/
#define	VIA_SR		0x000014	/*	Shift Register					*/
#define	VIA_ACR		0x000016	/*	Auxiliary Control Register		*/
#define	VIA_PCR		0x000018	/*	Peripheral Control Register		*/
#define	VIA_IFR		0x00001A	/*	Interrupt Flag Register			*/
#define	VIA_IER		0x00001C	/*	Interrupt Enable Register		*/
#define	VIA_NHIORA	0x00001E	/*	I/O Register A w/o Handshake	*/


/*		VIA Bit definitions		*/

#define	VBIT_DMA23		7		/*	PA7 - address bit 23 for DMA	*/
#define	VBIT_DMA22		6		/*	PA6 - address bit 22 for DMA	*/
#define	VBIT_TM0		5		/*	PA5 - TM0* from master trans.	*/
#define	VBIT_TM1		4		/*	PA4 - TM1* from master trans.	*/
#define	VBIT_JUMPER1	3		/*	PA3 - Configuration Jumper #1	*/
#define	VBIT_SHADOW		2		/*	PA2 - ROM Shadow bit			*/
#define	VBIT_RESET		1		/*	PA1 - 68000 Reset line			*/
#define	VBIT_JUMPER2	0		/*	PA0 - Configuration Jumper #2	*/

#define	VBIT_SCC1DSRA	7		/*	PA7 - SCC #1, DSR Channel A		*/
#define	VBIT_SCC1RIA	6		/*	PA6 - SCC #1, RI Channel A		*/
#define	VBIT_SCC1DSRB	5		/*	PA5 - SCC #1, DSR Channel B		*/
#define	VBIT_SCC1RIB	4		/*	PA4 - SCC #1, RI Channel B		*/
#define	VBIT_SCC2DSRA	3		/*	PA3 - SCC #2, DSR Channel A		*/
#define	VBIT_SCC2RIA	2		/*	PA2 - SCC #2, RI Channel A		*/
#define	VBIT_SCC2DSRB	1		/*	PA1 - SCC #2, DSR Channel B		*/
#define	VBIT_SCC2RIB	0		/*	PA0 - SCC #2, RI Channel B		*/

#define	VBIT_LEVEL1		0		/*	CA2 - Level 1 interupt to 68000	*/
#define	VBIT_NMRQ		1		/*	CB2 - NMRQ* to NuBus			*/

/*			Misc. Constants			*/

#define	CHKSUM_A1	0x0f081e	/*	First Checksum short Address	*/
#define	CHKSUM_A2	0x0f0530	/*	Second Checksum short Address	*/
#define CHKSUM_A3	0x0f0566	/*	Third Checksum short Address	*/
#define	CHKSUM_V1	0x87ad		/*	First Checksum short Value		*/
#define	CHKSUM_V2	0x9107		/*	Second Checksum short Value		*/
#define	CHKSUM_V3	0x1d41		/*	Third Checksum short Value		*/

#endif	SIOPDEF

/*		SCC Offset Addresses		*/

#define	MCP_SCC_ONE		0x100000		/*	Offset of SCC #1			*/
#define	MCP_SCC_TWO		0x000000		/*	Offset of SCC #2			*/

#define	MCP_SCC_CHA_A	0x000004		/*	Offset of Channel A			*/
#define	MCP_SCC_CHA_B	0x000000		/*	Offset of Channel B			*/

#define	MCP_SCC_COMMAND	0x000000		/*	Offset of Command Register	*/
#define	MCP_SCC_DATA	0x000002		/*	Offset of Data Register		*/

/*		Base Addresses		*/

#define	MCP_SCC_BASE	0x400000		/*	SCC base address						*/
#define	MCP_ROMBASE	0xFF0000		/*	ROM base address						*/
#define	MCP_CTLBASE	0xC00000		/*	Control register base address			*/
#define	MCP_NUBUS	0xA00000		/*	Nubus address							*/
#define	MCP_CTRESET	0xF00000		/*	Reset 68000								*/

#define	MCP_SELSCC	0xE				/*	Select SCC								*/
#define	MCP_SELX25	0xC				/*	Select any X25 mode						*/
#define	MCP_STIOPRQ	0xA				/*	Set interrupt IOP request				*/
#define	MCP_CRIOPRQ	0x8				/*	Clear interrupt IOP request				*/
#define	MCP_STHSTRQ	0x6				/*	Set interrupt host request				*/
#define	MCP_CRHSTRQ	0x4				/*	Clear interrupt host request			*/
#define	MCP_CLRTIMR	0x2				/*	Clear timer interrupt					*/
#define MCP_CLRREST	0x0				/*	clear 68000 reset						*/


#define	MCP_CHKSUMA1	MCP_ROMBASE+0xffea	/* location of MCP ROM magic number */
#define MCP_CHKSUMV1	0xc3d2				/* MCP ROM magic value			*/

#define	TICKS_PS	19						/*	19 ticks per second				*/
#define	TICK_MIN_MAJ 8						/* 8 minor ticks per major tick		*/

#endif

/*			End of siop.h			*/