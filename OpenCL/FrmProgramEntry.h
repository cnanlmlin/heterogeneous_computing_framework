#ifndef _FRM_PROGRAM_ENTRY_H_
#define _FRM_PROGRAM_ENTRY_H_

//#include "../FrmUtils.h"

struct ProgramEntry
{
	const char* name;
	const char* programStr;
	const char* programHash;
};

	extern const struct ProgramEntry FFT2D;
	extern const struct ProgramEntry simpleConvolution; 
	

#endif

