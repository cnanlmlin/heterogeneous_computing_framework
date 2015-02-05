#include "FrmPlatform.h"
#include "FrmUtils.h"

#include <ctime>
#include <android/log.h>

const char* g_log = "Unsupported";
char* g_pAppName = NULL;

int FrmSprintf(char* s, int n, const char* format, ...)
{
	va_list args;
	va_start(args, format);
	int ret = vsprintf( s, format, args );
	va_end(args);
	return ret;
}


void FrmAssert( signed int nExpression )
{
    assert( nExpression );
}

void FrmLogMessage( const char* strPrefix, const char* strMessage,
                    const char* strPostFix )
{
    //typedef enum android_LogPriority {
    //            ANDROID_LOG_UNKNOWN = 0,
    //            ANDROID_LOG_DEFAULT,    /* only for SetMinPriority() */
    //            ANDROID_LOG_VERBOSE,
    //            ANDROID_LOG_DEBUG,
    //            ANDROID_LOG_INFO,
    //            ANDROID_LOG_WARN,
    //            ANDROID_LOG_ERROR,
    //            ANDROID_LOG_FATAL,
    //            ANDROID_LOG_SILENT,     /* only for SetMinPriority(); must be last */
    //            } android_LogPriority;
#ifdef ANDROID_CL
    const CHAR* pLogTag = "OpenCL 1.1 Embedded Samples";
    if( g_pAppName != NULL )
        pLogTag = g_pAppName;
#else
    const char* pLogTag = "XXXToolkit";
#endif

    if( strPrefix )
        __android_log_write(ANDROID_LOG_INFO, pLogTag, strPrefix);
    if( strMessage )
        __android_log_write(ANDROID_LOG_INFO, pLogTag, strMessage);
    if( strPostFix )
        __android_log_write(ANDROID_LOG_INFO, pLogTag, strPostFix);

}

const char* FrmGetMessageLog()
{
    return g_log;
}

#ifndef CLOCKS_PER_SEC
#define CLOCKS_PER_SEC     1000000
#endif

float FrmGetTime()
{
	static bool		bInitialized = false;
	static clock_t	baseTime;

	if ( false == bInitialized )
	{
		baseTime = clock();
		bInitialized = true;
		return 0.0f;
	}

	float fAppTime = (float)(clock() - baseTime) / (float)CLOCKS_PER_SEC;
	return fAppTime;
}
