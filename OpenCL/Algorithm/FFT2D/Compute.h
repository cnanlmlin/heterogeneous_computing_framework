#ifndef _COMPUTE_H_
#define _COMPUTE_H_

#include "../../framework/FrmComputeApplication.h"
#include "FFT2D.h"

class CSample
{    
public:
    bool Compute( void* imgGrayInput, int width, int height, bool fft );

    CSample( const char* strName);

	bool Forward();
	bool Inverse();

private:

    bool CompareToRef( int nWidth, int nHeight, FFTComplex* pRefData, FFTComplex* pData,
                       float epsilon );

private:

    CFrmTimer m_Timer;

    cl_int m_nWidth;

    cl_int m_nHeight;
    
    CFFT2D* m_pFFT2D;

    FFTComplex* m_pInputArray;

};

#endif // _COMPUTE_H_
