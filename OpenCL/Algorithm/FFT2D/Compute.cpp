#include "Compute.h"

CSample::CSample( const char* strName)
{
    m_pFFT2D = NULL;
    m_pInputArray = NULL;

    m_nWidth = 1024; // Must be a power of 2
    m_nHeight = 1024; // Must be a power of 2
}

bool CSample::Initialize()
{
    cl_int errNum;
    m_pFFT2D = new CFFT2D(m_Timer);
    if ( false == m_pFFT2D->Initialize( m_context, m_devices[0], m_commandQueue ) )
    {
        return false;
    }

    return true;
}

void CSample::Destroy()
{
    if( m_commandQueue != 0 )
    {
        clReleaseCommandQueue( m_commandQueue );
        m_commandQueue = 0;
    }
}

bool CSample::CompareToRef( int nWidth, int nHeight, FFTComplex* pRefData, FFTComplex* pData,
                            float fEpsilon )
{
    bool result = true;

    for( int y = 0; y < nHeight; y++ )
    {
        for( int x = 0; x < nWidth; x++ )
        {
            FFTComplex refVal = pRefData[y * m_nWidth + x];
            FFTComplex val = pData[y * m_nWidth + x];

            if( std::abs( refVal.fReal - val.fReal ) > fEpsilon ||
                std::abs( refVal.fImaginary - val.fImaginary ) > fEpsilon )
            {
                char str[256];
                FrmSprintf( str, sizeof(str), "Reference test failure,(%d, %d): ref = (%f, %f), result = (%f, %f).\n",
                    y, x, refVal.fReal, refVal.fImaginary, val.fReal, val.fImaginary);
                FrmLogMessage( str );
                result = false;
            }
        }
    }

    return result;
}

bool CSample::Compute(void* imgGrayInput, int width, int height, bool fft )
{
	m_nWidth = width; // Must be a power of 2
	m_nHeight = height; // Must be a power of 2
    m_pInputArray = (FFTComplex*)imgGrayInput;

	if(fft){
		//FFT
		 return Forward();
	}
	else{
		//IFFT
		return Inverse();
	}
   
	return true;
	
}


bool CSample::Forward()
{
    bool ret = false;
    ret = m_pFFT2D->Forward( m_pInputArray, m_nWidth, m_nHeight, m_pInputArray );
    return ret;
}

bool CSample::Inverse()
{
	
	bool ret = m_pFFT2D->Inverse( m_pInputArray, m_nWidth, m_nHeight, m_pInputArray );
	ret = true;

	return ret;
}

