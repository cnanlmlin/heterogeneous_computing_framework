#include "FrmPlatform.h"
#include "FrmUtils.h"
#include "FrmFile.h"

bool FrmLoadFile( const char* strFileName, void** ppData, unsigned int* pnSize )
{
	FRM_FILE* pFile;
	if( false == FrmFile_Open( strFileName, FRM_FILE_READ, &pFile ) )
		return false;

	unsigned int nSize = FrmFile_GetSize( pFile );

	if( 0 == nSize )
	{
		FrmFile_Close( pFile );
		return false;
	}

	if( ppData )
	{
		BYTE* pData = new BYTE[nSize+1];
		FrmFile_Read( pFile, pData, nSize );
		pData[nSize] = 0;

		(*ppData) = pData;
	}

	if( pnSize )
		(*pnSize) = nSize;

	FrmFile_Close( pFile );
	return true;
}

void FrmUnloadFile( void* pData )
{
    delete[] pData;
}
