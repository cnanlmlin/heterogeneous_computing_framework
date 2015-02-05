#include <ctime>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>

#include <string>
#include <vector>
#include <cstdlib>

#include <assert.h>


#define CHECK_ALLOCATION(actual, msg) \
	if(actual == NULL) \
	{ \
	error(msg); \
	std::cout << "Location : " << __FILE__ << ":" << __LINE__<< std::endl; \
	return 1; \
	}

static void error(std::string errorMsg)
{
	std::cout<<"Error: "<<errorMsg<<std::endl;
}

static const float FRM_PI = 3.1415926f;


int FrmSprintf(char* s, int n, const char* format, ...);

float FrmGetTime();

void FrmAssert( signed int nExpression );
void FrmLogMessage( const char* strPrefix, const char* strMessage=NULL,
                    const char* strPostFix=NULL );
const char* FrmGetMessageLog();

bool FrmLoadFile( const char* strFileName, void** ppData, signed int* pnSize = NULL );
void FrmUnloadFile( void* pData );

class CFrmTimer
{
public:
	CFrmTimer()
	{
		m_fLastTime       = FrmGetTime();

		m_strFrameRate[0] = '\0';
		m_fFPS            = 0.0f;
		m_fFrameRateTime  = m_fLastTime;
		m_nFrame          = 0;

		Reset();
		Start();
	}

	float Start()
	{
		m_bRunning = true;
		m_fStartTime = FrmGetTime();
		return m_fTotalTimeBeforeLastStart;
	};

	float Stop()
	{
		m_bRunning = false;
		float fTimeSinceLastStart = FrmGetTime() - m_fStartTime;
		m_fTotalTimeBeforeLastStart += fTimeSinceLastStart;
		return m_fTotalTimeBeforeLastStart;
	}

	void Reset()
	{
		m_bRunning = false;
		m_fTotalTimeBeforeLastStart = 0.0f;
		m_fStartTime = 0.0f;
		m_fElapsedTime = 0.0f;
	}

	float GetTime()
	{
		if( m_bRunning )
		{
			float fTimeSinceLastStart = FrmGetTime() - m_fStartTime;
			return m_fTotalTimeBeforeLastStart + fTimeSinceLastStart;
		}
		return m_fTotalTimeBeforeLastStart;
	}

	float GetFrameTime()
	{
		return m_fLastTime;
	}

	float GetFrameElapsedTime()
	{
		return m_fElapsedTime;
	}

	void MarkFrame()
	{
		m_nFrame++;

		float fCurrentTime = FrmGetTime();
		m_fElapsedTime = fCurrentTime - m_fLastTime;
		m_fLastTime    = fCurrentTime;
	}

	float GetFrameRate()
	{
		float fCurrentTime = FrmGetTime();

		if( fCurrentTime - m_fFrameRateTime > 1.0f )
		{
			m_fFPS = m_nFrame / ( fCurrentTime - m_fFrameRateTime );
			m_fFrameRateTime = fCurrentTime;
			m_nFrame         = 0;
			return m_fFPS;
		}
		return m_fFPS;
	}

	const char* GetFrameRateStr()
	{
		FrmSprintf( m_strFrameRate, 20, "%3.1f fps", GetFrameRate() );
		return m_strFrameRate;
	}

public:
	bool    m_bRunning;
	float m_fTotalTimeBeforeLastStart;
	float m_fStartTime;
	float m_fElapsedTime;
	float m_fLastTime;

	char    m_strFrameRate[20];
	float m_fFPS;
	float m_fFrameRateTime;
	int  m_nFrame;
};


