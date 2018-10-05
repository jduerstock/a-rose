/****************************************************************************************/
/*																						*/
/*							scc.h - SCC interupt handler table.							*/
/*																						*/
/*					Richard W. Mincher.						06/06/87.					*/
/*																						*/
/*					Copyright Apple Computer, Inc. 1987-88								*/
/*					All rights reserved.												*/
/****************************************************************************************/

#ifndef						_scc_defined_
#define	_scc_defined_

struct	sccint
{

	/*	PROCESSORS	*/

	void	(*chbtbep)();			/*	 ch b transmit buffer empty procedure		*/
	void	(*chbescp)();			/*	 ch b external/status change procedure		*/
	void	(*chbrcap)();			/*	 ch b receive character available procedure	*/
	void	(*chbrscp)();			/*	 ch b receive special condition procedure	*/
	void	(*chatbep)();			/*	 ch a transmit buffer empty procedure		*/
	void	(*chaescp)();			/*	 ch a external/status change procedure		*/
	void	(*charcap)();			/*	 ch a receive character available procedure	*/
	void	(*charscp)();			/*	 ch a receive special condition procedure	*/

/*	COUNTERS	*/

	long	chbtbec;
	long	chbescc;
	long	chbrcac;
	long	chbrscc;
	long	chatbec;
	long	chaescc;
	long	charcac;
	long	charscc;

/*	ARGUMENTS	*/

	long	chbtbea;
	long	chbesca;
	long	chbrcaa;
	long	chbrsca;
	long	chatbea;
	long	chaesca;
	long	charcaa;
	long	charsca;
};


typedef	struct	sccint	scctable;

#endif