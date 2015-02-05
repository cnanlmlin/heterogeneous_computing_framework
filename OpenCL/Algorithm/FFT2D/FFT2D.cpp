#include "../../framework/OpenCL/FrmKernel.h"
#include "FFT2D.h"

CFFT2D::CFFT2D(CFrmTimer& t)
: m_context(0),
  m_commandQueue(0),
  timer(t)
{
    for( int i = 0; i < NUM_FFT_KERNELS; i++ )
    {
        m_kernels[i] = 0;
    }
}

CFFT2D::~CFFT2D()
{
    Destroy();
}

bool CFFT2D::Initialize( cl_context context, cl_device_id device, cl_command_queue commandQueue )
{
    m_context = context;

	m_device = device;

    m_commandQueue = commandQueue;
    cl_program program;
    cl_int errNum = 0;
    char options[256]=" ";

    errNum = clGetDeviceInfo(device, CL_DEVICE_TYPE, sizeof(devType), &devType, NULL);
    if ( errNum != CL_SUCCESS )
    {
        FrmLogMessage( "Failed to obtain device type" );
        return false;
    }


    if (devType == CL_DEVICE_TYPE_GPU)
    {
        strncat(options, " -cl-fast-relaxed-math ", sizeof(options));
        strncat(options, " -DQC_OPT ", sizeof(options));
    }

	if( false == FrmGetOrBuildComputeProgramFromFile(&FFT2D, &program, context,
		&device, 1, options ) )
	{
		return false;
	}

    const char* kernelNames[NUM_FFT_KERNELS] = {0};

    if (devType == CL_DEVICE_TYPE_CPU)
    {
        kernelNames[FFT_RADIX_2]  = "FFT2DRadix2";
        kernelNames[IFFT_RADIX_2] = "IFFT2DRadix2";
        kernelNames[FFT_RADIX_4]  = "FFT2DRadix2"; 
    }
    else
    {
        kernelNames[FFT_RADIX_2]  = "FFT2DRadix2_P0";
        kernelNames[IFFT_RADIX_2] = "FFT2DRadix2_P0";
        kernelNames[FFT_RADIX_4]  = "FFT2DRadix4";
    }

    kernelNames[MATRIX_TRANSPOSE] = "MatrixTranspose";

    for( int i = 0; i < NUM_FFT_KERNELS; i++ )
    {
        m_kernels[i] = clCreateKernel( program, kernelNames[ i ], &errNum );
        if ( errNum != CL_SUCCESS )
        {
            char str[256];
            FrmSprintf( str, sizeof(str), "ERROR: Failed to create kernel '%s'.\n", kernelNames[i] );
	    FrmLogMessage( str );
            return false;
        }
    }

    clReleaseProgram( program );

    return true;
}

void CFFT2D::Destroy()
{
    for( int i = 0; i < NUM_FFT_KERNELS; i++ )
    {
        if( m_kernels[i] != 0 )
        {
            clReleaseKernel( m_kernels[i] );
            m_kernels[i] = 0;
        }
    }
}

bool CFFT2D::Forward( const FFTComplex* pInArray, int nWidth, int nHeight,
                      FFTComplex* pOutArray, bool bRefCPU )
{
    if ( bRefCPU )
    {
        ForwardRef( pInArray, nWidth, nHeight, pOutArray );
        return true;
    }
    else
    {
        return ExecuteRadix2FFT( FFT_RADIX_2, pInArray, nWidth, nHeight, pOutArray );
    }
}

bool CFFT2D::Inverse( const FFTComplex* pInArray, int nWidth, int nHeight,
                      FFTComplex* pOutArray, bool bRefCPU )
{
    if ( bRefCPU )
    {
        InverseRef( pInArray, nWidth, nHeight, pOutArray );
        return true;
    }
    else
    {
        return ExecuteRadix2FFT( IFFT_RADIX_2, pInArray, nWidth, nHeight, pOutArray );
    }
}

bool CFFT2D::ExecuteRadix2FFT( KernelType kernelType, const FFTComplex* pInArray,
                               int nWidth, int nHeight, FFTComplex* pOutArray )
{
    cl_kernel kernel = m_kernels[ (int) kernelType ];
    cl_int errNum = 0;
    cl_mem inArray = 0, outArray = 0, scratchArray = 0;

    if( false == AllocateMemObjects( nWidth, nHeight, pInArray,
                                     &inArray, &outArray, &scratchArray ) )
    {
        return false;
    }
    timer.Start();

    bool result;
    cl_mem memObjs[2] = { inArray, outArray };
    result = ExecuteRowWiseRadix2FFT( kernelType, memObjs, nWidth, nHeight );
    if( false == result )
        return false;

    result = ExecuteTranspose( nWidth, nHeight, memObjs[0], scratchArray );
    if( false == result )
        return false;

    memObjs[0] = scratchArray;
    memObjs[1] = outArray;

    result = ExecuteRowWiseRadix2FFT( kernelType, memObjs, nHeight, nWidth );
    if( false == result )
        return false;
    result = ExecuteTranspose( nHeight, nWidth, memObjs[0], memObjs[1] );
    if( false == result )
        return false;

    clFinish(m_commandQueue);

    timer.Stop();
    errNum = clEnqueueReadBuffer( m_commandQueue, memObjs[1], CL_TRUE, 0, sizeof(FFTComplex) * nWidth * nHeight,
        pOutArray, 0, NULL, NULL );
    if( errNum != CL_SUCCESS )
    {
        FrmLogMessage( "Error enqueuing buffer read." );
        return false;
    }

    clReleaseMemObject( inArray );
    clReleaseMemObject( outArray );
    clReleaseMemObject( scratchArray );
    return true;
}

bool CFFT2D::ExecuteRowWiseRadix2FFT( KernelType kernelType, cl_mem memObjs[2],
                                      int nWidth, int nHeight )
{
	bool ret = false;
    if (devType == CL_DEVICE_TYPE_GPU)
    {
        ret = ExecuteRowWiseRadix2FFTOpt(kernelType, memObjs, nWidth, nHeight);
    }
    else
    {
        ret = ExecuteRowWiseRadix2FFTOrig(kernelType, memObjs, nWidth, nHeight);
    }
	return ret;
}

bool CFFT2D::ExecuteRowWiseRadix2FFTOrig( KernelType kernelType, cl_mem memObjs[2],
                                      int nWidth, int nHeight )
{
    cl_kernel kernel = m_kernels[ (int) kernelType ];
    cl_int errNum = 0;

    if ( kernelType == IFFT_RADIX_2 )
    {
        cl_float oneOverN = 1.0f / (cl_float) nWidth;
        errNum = clSetKernelArg( kernel, 4, sizeof(cl_float), &oneOverN );
    }

    errNum |= clSetKernelArg( kernel, 0, sizeof(cl_int), &nWidth );
    for( int p = 1; p <= nWidth / 2; p *= 2 )
    {
        size_t globalWorkSize[2] = { nWidth / 2,  nHeight };

        errNum |= clSetKernelArg( kernel, 1, sizeof(cl_int), &p );

        errNum |= clSetKernelArg( kernel, 2, sizeof(cl_mem), &memObjs[0] );
        errNum |= clSetKernelArg( kernel, 3, sizeof(cl_mem), &memObjs[1] );

        if( errNum != CL_SUCCESS )
        {
            FrmLogMessage( "Error setting kernel arguments" );
            return false;
        }

        errNum = clEnqueueNDRangeKernel( m_commandQueue, kernel, 2, NULL,
                                        globalWorkSize, NULL, 0, NULL, NULL );
        if( errNum != CL_SUCCESS )
        {
            char str[256];
            FrmSprintf( str, sizeof(str), "Error queueing Radix2 kernel for execution (%d).\n", errNum );
            FrmLogMessage( str );
	    return false;
        }

        cl_mem temp = memObjs[1];
        memObjs[1] = memObjs[0];
        memObjs[0] = temp;
    }

    return true;
}

bool CFFT2D::ExecuteRowWiseRadix2FFTOpt( KernelType kernelType, cl_mem memObjs[2],
                                      int nWidth, int nHeight )
{
    cl_kernel kernel;
    cl_int errNum = 0;
    int p = 1;
    cl_float oneOverN = 1.0f / nWidth;
    int m = 0;
    int sign;
    float oneOverP;

    {
        int n = nWidth;
        while(n>>=1)
            m++;
    }

    if(m & 1)
    {
        kernel = m_kernels[ (int) FFT_RADIX_2 ];

        size_t gws[2] = { nWidth / 4,  nHeight };
        size_t lws[2] = { 128, 1 };
        size_t* lwsp = lws;

        if(nWidth < 4 * lws[0])
            lwsp = NULL;

        errNum |= clSetKernelArg( kernel, 0, sizeof(cl_int), &nWidth );
        errNum |= clSetKernelArg( kernel, 1, sizeof(cl_mem), &memObjs[0] );
        errNum |= clSetKernelArg( kernel, 2, sizeof(cl_mem), &memObjs[1] );
        errNum |= clSetKernelArg( kernel, 3, sizeof(cl_int), &m );

        if( errNum != CL_SUCCESS )
        {
            FrmLogMessage( "Error setting kernel arguments" );
            return false;
        }
		
		errNum = clEnqueueNDRangeKernel( m_commandQueue, kernel, 2, NULL,
                                        gws, lwsp, 0, NULL, NULL );
        if( errNum != CL_SUCCESS )
        {
            char str[256];
            FrmSprintf( str, sizeof(str), "Error queueing Radix2 kernel pass for execution (%d).\n", errNum );
            FrmLogMessage( str );
            return false;
        }

        cl_mem temp = memObjs[1];
        memObjs[1] = memObjs[0];
        memObjs[0] = temp;

        p = 2;

    }
    else
    {
        p  = 1;
    }

    kernel = m_kernels[ (int) FFT_RADIX_4 ];

    size_t globalWorkSize[2] = { nWidth / 4,  nHeight };
    size_t localWorkSize[2] = { 128, 1 };
    size_t* lws = localWorkSize;

    if(nWidth < 4 * localWorkSize[0])
        lws = NULL;

    if ( kernelType == IFFT_RADIX_2 )
    {
        sign = 1;
        oneOverN = 1.0f / nWidth;
    }
    else
    {
        sign = -1;
        oneOverN = 1.0f;
    }

    errNum |= clSetKernelArg( kernel, 0, sizeof(cl_int), &nWidth );
    errNum |= clSetKernelArg( kernel, 4, sizeof(cl_float), &oneOverN );
    errNum |= clSetKernelArg( kernel, 5, sizeof(cl_int), &m );
    errNum |= clSetKernelArg( kernel, 6, sizeof(cl_int), &sign );

    for(; p <= nWidth / 4; p *= 4 )
    {
        oneOverP = 1.f / (float)p;
        errNum |= clSetKernelArg( kernel, 1, sizeof(cl_int), &p );
        errNum |= clSetKernelArg( kernel, 2, sizeof(cl_mem), &memObjs[0] );
        errNum |= clSetKernelArg( kernel, 3, sizeof(cl_mem), &memObjs[1] );
        errNum |= clSetKernelArg( kernel, 7, sizeof(cl_float), &oneOverP );
        if( errNum != CL_SUCCESS )
        {
        FrmLogMessage( "Error setting kernel arguments" );
        return false;
    }

    errNum = clEnqueueNDRangeKernel( m_commandQueue, kernel, 2, NULL,
                                    globalWorkSize, lws, 0, NULL, NULL );
    if( errNum != CL_SUCCESS )
    {
        char str[256];
        FrmSprintf( str, sizeof(str), "Error queueing Radix4 kernel for execution (%d).\n", errNum );
        FrmLogMessage( str );
        return false;
    }

    cl_mem temp = memObjs[1];
    memObjs[1] = memObjs[0];
    memObjs[0] = temp;

    }
    return true;
}

bool CFFT2D::ExecuteTranspose( int nCols, int nRows, cl_mem inputMat, cl_mem outputMat )
{
    cl_kernel kernel = m_kernels[ MATRIX_TRANSPOSE ];
    cl_int errNum = 0;
    errNum |= clSetKernelArg( kernel, 0, sizeof(int), &nRows);
    errNum |= clSetKernelArg( kernel, 1, sizeof(int), &nCols );
    errNum |= clSetKernelArg( kernel, 2, sizeof(cl_mem), &inputMat );
    errNum |= clSetKernelArg( kernel, 3, sizeof(cl_mem), &outputMat );
    if( errNum != CL_SUCCESS )
    {
        FrmLogMessage( "Error setting kernel arguments for MatrixTranspose kernel.\n" );
		return false;
    }

    if (devType == CL_DEVICE_TYPE_GPU)
    {
        size_t globalWorkSize[2] = { nCols / 2, nRows / 2};
        size_t localWorkSize[2] = {4, 64};
        errNum = clEnqueueNDRangeKernel( m_commandQueue, kernel, 2, NULL,
                                     globalWorkSize, localWorkSize, 0, NULL, NULL );

    }
    else
    {
        size_t globalWorkSize[1] = { nRows };
        errNum = clEnqueueNDRangeKernel( m_commandQueue, kernel, 1, NULL,
                                     globalWorkSize, NULL, 0, NULL, NULL );

    }


    if( errNum != CL_SUCCESS )
    {
        FrmLogMessage( "Error queueing transpose kernel for execution.\n" );
        return false;
    }

    return true;
}

bool CFFT2D::AllocateMemObjects( int nWidth, int nHeight, const FFTComplex* pInArray,
                                 cl_mem* pObjIn, cl_mem* pObjOut, cl_mem *pObjScratch )
{
    cl_int nArraySize = nWidth * nHeight;
    cl_int errNum = 0;
    *pObjIn = clCreateBuffer( m_context, CL_MEM_READ_WRITE | CL_MEM_COPY_HOST_PTR, nArraySize * sizeof(FFTComplex),
                              (void*)pInArray, &errNum );
    if( errNum != CL_SUCCESS )
    {
        FrmLogMessage( "ERROR: allocation of device input array.\n" );
        return false;
    }

    *pObjOut = clCreateBuffer( m_context, CL_MEM_READ_WRITE, nArraySize * sizeof(FFTComplex), NULL, &errNum );
    if( errNum != CL_SUCCESS )
    {
        clReleaseMemObject( *pObjIn );
        *pObjIn = 0;
        FrmLogMessage( "ERROR: allocation of device output array.\n" );
        return false;
    }

    *pObjScratch = clCreateBuffer( m_context, CL_MEM_READ_WRITE, nArraySize * sizeof(FFTComplex), NULL, &errNum );
    if( errNum != CL_SUCCESS )
    {
        clReleaseMemObject( *pObjIn );
        clReleaseMemObject( *pObjOut );
        *pObjIn = 0;
        *pObjOut = 0;
        FrmLogMessage( "ERROR: allocation of device scratch array.\n" );
        return false;
    }

    return true;
}

void CFFT2D::ForwardRef( const FFTComplex* pInArray, int nWidth, int nHeight,
                         FFTComplex* pOutArray )
{
    ForwardOrInverseRef( pInArray, nWidth, nHeight, pOutArray, FORWARD );
}

void CFFT2D::InverseRef( const FFTComplex* pInArray, int nWidth, int nHeight,
                         FFTComplex* pOutArray )
{
    ForwardOrInverseRef( pInArray, nWidth, nHeight, pOutArray, INVERSE );
}

void CFFT2D::ForwardOrInverseRef( const FFTComplex* pInArray, int nWidth, int nHeight,
                                     FFTComplex* pOutArray, Direction eDirection )
{
    FFTComplex* pScratch = new FFTComplex[ nWidth ];

    for( int y = 0; y < nHeight; y++ )
    {
        const FFTComplex* pInRowData = &pInArray[y * nWidth];
        FFTComplex* pOutRowData = &pOutArray[y * nWidth];

        if( eDirection == FORWARD )
            FFTRef( nWidth, 0, 1, pInRowData, pOutRowData, pScratch );
        else
            IFFTRef( nWidth, pInRowData, pOutRowData );
    }
    delete [] pScratch;

    pScratch = new FFTComplex[ nHeight ];

    FFTComplex* pTransposedOutput = new FFTComplex[ nWidth * nHeight ];

    FFTComplex* pRowFFTArrayT = new FFTComplex[ nHeight * nWidth ];
    TransposeRef( nWidth, nHeight, pOutArray, pRowFFTArrayT );

    for( int x = 0; x < nWidth; x++ )
    {
        const FFTComplex* pInColData = &pRowFFTArrayT[x * nHeight];
        FFTComplex* pOutColData = &pTransposedOutput[x * nHeight];

        if( eDirection == FORWARD )
            FFTRef( nHeight, 0, 1, pInColData, pOutColData, pScratch );
        else
            IFFTRef( nHeight, pInColData, pOutColData );
    }
    delete [] pScratch;

    TransposeRef( nHeight, nWidth, pTransposedOutput, pOutArray );

    delete [] pRowFFTArrayT;
    delete [] pTransposedOutput;
}

void CFFT2D::FFTRef( int nArraySize, int nOffset, int nDelta, const FFTComplex* pInData,
                     FFTComplex* pOutData, FFTComplex* pScratch )
{
    int nHalfSize = nArraySize / 2;

    if( nArraySize != 2 )
    {
        FFTRef( nHalfSize, nOffset, 2 * nDelta, pInData, pScratch, pOutData );
        FFTRef( nHalfSize, nOffset + nDelta, 2 * nDelta, pInData, pScratch, pOutData );

        for( int k = 0; k < nHalfSize; k++ )
        {
            int k00 = nOffset + k * nDelta;
            int k01 = k00 + nHalfSize * nDelta;
            int k10 = nOffset + 2 * k * nDelta;
            int k11 = k10 + nDelta;

            float fCos = std::cos( 2.0f * FRM_PI * k / (float) nArraySize );
            float fSin = std::sin( 2.0f * FRM_PI * k / (float) nArraySize );

            float fTmp0 = fCos * pScratch[k11].fReal + fSin * pScratch[k11].fImaginary;
            float fTmp1 = fCos * pScratch[k11].fImaginary - fSin * pScratch[k11].fReal;

            pOutData[k01].fReal = pScratch[k10].fReal - fTmp0;
            pOutData[k01].fImaginary = pScratch[k10].fImaginary - fTmp1;
            pOutData[k00].fReal = pScratch[k10].fReal + fTmp0;
            pOutData[k00].fImaginary = pScratch[k10].fImaginary + fTmp1;
        }
    }
    else
    {
        int k00 = nOffset;
        int k01 = k00 + nDelta;
        pOutData[k01].fReal = pInData[k00].fReal - pInData[k01].fReal;
        pOutData[k01].fImaginary = pInData[k00].fImaginary - pInData[k01].fImaginary;
        pOutData[k00].fReal = pInData[k00].fReal + pInData[k01].fReal;
        pOutData[k00].fImaginary = pInData[k00].fImaginary + pInData[k01].fImaginary;

    }
}

void CFFT2D::IFFTRef( int nArraySize, const FFTComplex* pInData,
                      FFTComplex* pOutData )
{
    FFTComplex* pScratch = new FFTComplex[ nArraySize ];
    FFTRef( nArraySize, 0, 1, pInData, pOutData, pScratch );

    int nHalfSize = nArraySize / 2;
    pOutData[0].fReal = pOutData[0].fReal / nArraySize;
    pOutData[0].fImaginary = pOutData[0].fImaginary / nArraySize;

    pOutData[nHalfSize].fReal = pOutData[nHalfSize].fReal / nArraySize;
    pOutData[nHalfSize].fImaginary = pOutData[nHalfSize].fImaginary / nArraySize;

    for( int i = 1; i < nHalfSize; i++ )
    {
        FFTComplex temp = pOutData[i];
        temp.fReal /= nArraySize;
        temp.fImaginary /= nArraySize;

        pOutData[i].fReal = pOutData[nArraySize - i].fReal / nArraySize;
        pOutData[i].fImaginary = pOutData[nArraySize - i].fImaginary / nArraySize;

        pOutData[nArraySize - i] = temp;
    }
}

void CFFT2D::TransposeRef( int nWidth, int nHeight, const FFTComplex* pInData,
                           FFTComplex* pOutData )
{
    for( int y = 0; y < nHeight; y++ )
    {
        for( int x = 0; x < nWidth; x++ )
        {
            pOutData[x * nHeight + y] = pInData[y * nWidth + x];
        }
    }
}
