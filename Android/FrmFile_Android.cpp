#include "FrmFile.h"
#include "FrmUtils.h"
#include <android_native_app_glue.h>

struct FRM_FILE
{
};

AAssetManager* g_pAssetManager = 0;
const char* g_pInternalDataPath;

bool FrmFile_Open( const char* strFileName, unsigned int nDirection, FRM_FILE** ppFile )
{
    if( nDirection == FRM_FILE_READ )
    {
	    AAsset* asset = AAssetManager_open(g_pAssetManager, strFileName, AASSET_MODE_STREAMING);
	    *ppFile = (FRM_FILE*)asset;
	    LOGI("Opened asset %s at %x", strFileName, (unsigned int)asset);
	    return asset ? true : false;
    }
    else if( nDirection == FRM_FILE_WRITE )
    {
        const char *internalDataPath = g_pInternalDataPath;
        if( internalDataPath == NULL )
            return false;

        char fullPath[1024];
        char logMsg[1024];
        FrmSprintf( fullPath, sizeof(fullPath), "%s/%s", internalDataPath, strFileName );
        FrmSprintf( logMsg, sizeof(logMsg), "Opening file for writing: %s", fullPath );
        FrmLogMessage( logMsg, NULL, NULL );
        *ppFile = (FRM_FILE*)fopen( fullPath, "wb" );
        return *ppFile ? true : false;
    }

    return false;
}

void FrmFile_Close( FRM_FILE* pFile, unsigned int nDirection )
{
    if( nDirection == FRM_FILE_READ )
    {
        AAsset_close((AAsset*)pFile);
    }
    else
    {
        fclose((FILE*)pFile);
    }
}

unsigned int FrmFile_Read( FRM_FILE* pFile, void* ptr, unsigned int nSize )
{
	return AAsset_read((AAsset*) pFile, ptr, nSize);
}

unsigned int FrmFile_Write( FRM_FILE* pFile, void* ptr, unsigned int nSize )
{
    return fwrite( ptr, nSize, 1, (FILE*)pFile );
}

unsigned int FrmFile_GetSize( FRM_FILE* pFile )
{
	unsigned int nSize = AAsset_getRemainingLength((AAsset*)pFile);
	LOGI("GetSize returned %d", nSize);
    return nSize;
}
