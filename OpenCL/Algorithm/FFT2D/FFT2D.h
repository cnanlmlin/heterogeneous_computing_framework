#ifndef _FFT2D_H
#define _FFT2D_H
#include <CL/cl.h>
#include "../../framework/FrmUtils.h"

typedef struct
{
    float fReal;
    float fImaginary;

}  FFTComplex;

class CFFT2D
{
public:
    typedef enum
    {
        FFT_RADIX_2 = 0,
        IFFT_RADIX_2,
        FFT_RADIX_4,
        MATRIX_TRANSPOSE,
        NUM_FFT_KERNELS
    } KernelType;

    typedef enum
    {
        FORWARD,
        INVERSE
    } Direction;

    CFFT2D(CFrmTimer& t);
    virtual ~CFFT2D();

    bool Initialize( cl_context context, cl_device_id device, cl_command_queue commandQueue );

    bool Forward( const FFTComplex* pInArray, int nWidth, int nHeight,
                  FFTComplex* pOutArray, bool bRefCPU = false );

    bool Inverse( const FFTComplex* pInArray, int nWidth, int nHeight,
                  FFTComplex* pOutArray, bool bRefCPU = false );

private:

    void ForwardRef( const FFTComplex* pInArray, int nWidth, int nHeight,
                     FFTComplex* pOutArray );

    void InverseRef( const FFTComplex* pInArray, int nWidth, int nHeight,
                     FFTComplex* pOutArray );

    bool ExecuteRadix2FFT( KernelType kernelType, const FFTComplex* pInArray,
                           int nWidth, int nHeight, FFTComplex* pOutArray );

    bool ExecuteRowWiseRadix2FFT( KernelType kernelType, cl_mem memObjs[2],
                                  int nWidth, int nHeight );

    bool ExecuteTranspose( int nRows, int nCols, cl_mem inputMat, cl_mem outputMat );

    bool AllocateMemObjects( int nWidth, int nHeight, const FFTComplex* pInArray,
                             cl_mem* pObjIn, cl_mem* pObjOut, cl_mem* pObjScratch );

    void ForwardOrInverseRef( const FFTComplex* pInArray, int nWidth, int nHeight,
                              FFTComplex* pOutArray, Direction eDirection );

    void FFTRef( int nArraySize, int nOffset, int nDelta, const FFTComplex* pInData,
                 FFTComplex* pOutData, FFTComplex* pScratch );

    void IFFTRef( int nArraySize, const FFTComplex* pInData,
                  FFTComplex* pOutData );


    void TransposeRef( int nWidth, int nHeight, const FFTComplex* pInData,
                       FFTComplex* pOutData );

    void Destroy();



private:

    bool ExecuteRowWiseRadix2FFTOrig( KernelType kernelType, cl_mem memObjs[2],
                                  int nWidth, int nHeight );

    bool ExecuteRowWiseRadix2FFTOpt( KernelType kernelType, cl_mem memObjs[2],
                                  int nWidth, int nHeight );


    cl_context m_context;

	cl_device_id m_device;

    cl_command_queue m_commandQueue;

    cl_kernel m_kernels[NUM_FFT_KERNELS];

    CFrmTimer& timer;
    cl_device_type devType;

};

#endif // _FFT2D_H
