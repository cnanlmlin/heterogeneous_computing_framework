#ifndef _FRM_FILE_H_
#define _FRM_FILE_H_

#include "FrmPlatform.h"

struct FRM_FILE;

const unsigned int FRM_FILE_READ      = 0;
const unsigned int FRM_FILE_WRITE     = 1;
const unsigned int FRM_FILE_READWRITE = 2;

#ifndef UNDER_CE
	bool   FrmFile_Open( const char* strFileName, unsigned int nDirection, FRM_FILE** ppFile );
    void   FrmFile_Close( FRM_FILE* pFile, unsigned int nDirection = FRM_FILE_READ );
    unsigned int FrmFile_Read( FRM_FILE* pFile, void* ptr, unsigned int size );
    unsigned int FrmFile_Write( FRM_FILE* pFile, void* ptr, unsigned int size );
    unsigned int FrmFile_GetSize( FRM_FILE* pFile );
#else
    bool   FrmFile_Open( const char* strFileName, unsigned int nDirection, FILE** ppFile );
    void   FrmFile_Close( FILE* pFile, unsigned int nDirection = FRM_FILE_READ );
    unsigned int FrmFile_Read( FILE* pFile, void* ptr, unsigned int size );
    unsigned int FrmFile_Write( FILE* pFile, void* ptr, unsigned int size );
    unsigned int FrmFile_GetSize( FILE* pFile );
#endif


#endif
