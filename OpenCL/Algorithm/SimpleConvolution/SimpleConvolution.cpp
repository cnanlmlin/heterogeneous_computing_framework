#include "../../framework/OpenCL/FrmKernel.h"
#include "../../framework/OpenCL/FrmOCLUtils.h"
#include "SimpleConvolution.h"

SimpleConvolution::SimpleConvolution(int nWidth, int nHeight, int mWidth, int mHeight)
: m_context(0),
  m_commandQueue(0),
  m_device(0),
  m_kernel(0)
{
	input = NULL;
	output = NULL;
	mask   = NULL;
	width = nWidth;
	height = nHeight;
	maskWidth = mWidth;
	maskHeight = mHeight;
	//totalKernelTime = 0;
	iterations = 1;
}

SimpleConvolution::~SimpleConvolution(){
	Destroy();
}

bool SimpleConvolution::Initialize( cl_context context, cl_device_id device, cl_command_queue commandQueue ){
	m_context = context;
	m_device = device;
	m_commandQueue = commandQueue;
	cl_program m_program;
	cl_int errNum = 0;
	if( false == FrmGetOrBuildComputeProgramFromFile(&simpleConvolution, &m_program, m_context, &m_device, 1) ){
		return false;
	}

	m_kernel = clCreateKernel(m_program, "simpleConvolution", &errNum);
	if(errNum != CL_SUCCESS){
		char str[256];
		FrmSprintf( str, sizeof(str), "ERROR: Failed to create kernel simpleConvolution.\n" );
		FrmLogMessage( str );
		return false;
	}
	clReleaseProgram(m_program);
	return true;
}

bool SimpleConvolution::runCLKernels( const float* pInArray, const float* pMaskArray, float* pOutArray){
	cl_mem inputBuffer = 0, maskBuffer = 0, outputBuffer = 0;
	//cl_int nArraySize = width * height;
	cl_int errNum = 0;
	cl_event events[2];
	inputBuffer = clCreateBuffer(m_context, CL_MEM_READ_WRITE | CL_MEM_COPY_HOST_PTR, width*height*sizeof(float), (void*)pInArray, &errNum );
	if(errNum != CL_SUCCESS){
		printf( "ERROR: allocation of device input array.\n" );
		return false;
	}
	maskBuffer = clCreateBuffer(m_context, CL_MEM_READ_ONLY | CL_MEM_USE_HOST_PTR, maskWidth*maskHeight*sizeof(float), (void*)pMaskArray, &errNum);
	if(errNum != CL_SUCCESS){
		clReleaseMemObject(inputBuffer);
		printf( "ERROR: allocation of device input array.\n" );
		return false;
	}
	outputBuffer = clCreateBuffer(m_context, CL_MEM_READ_WRITE, width*height*sizeof(float), NULL, &errNum );
	if(errNum != CL_SUCCESS){
		clReleaseMemObject(inputBuffer);
		clReleaseMemObject(maskBuffer);
		printf( "ERROR: allocation of device input array.\n" );
		return false;
	}

	size_t gws[1] = { width * height };
	size_t lws[1] = { 256 };
	errNum |= clSetKernelArg( m_kernel, 0, sizeof(cl_mem), (void *)&outputBuffer );
	errNum |= clSetKernelArg( m_kernel, 1, sizeof(cl_mem), (void *)&inputBuffer);
	errNum |= clSetKernelArg( m_kernel, 2, sizeof(cl_mem), (void *)&maskBuffer);
	cl_uint2 inputDimensions = {width, height};
	cl_uint2 maskDimensions  = {maskWidth, maskHeight};
	errNum |= clSetKernelArg( m_kernel, 3, sizeof(cl_uint2), (void *)&inputDimensions );
	errNum |= clSetKernelArg( m_kernel, 4, sizeof(cl_uint2), (void *)&maskDimensions );
	if( errNum != CL_SUCCESS )
	{
		FrmLogMessage( "Error setting kernel arguments" );
		return false;
	}

	errNum = clEnqueueNDRangeKernel( m_commandQueue, m_kernel, 1, NULL,
		gws, lws, 0, NULL, &events[0] );
	if( errNum != CL_SUCCESS )
	{
		FrmLogMessage( "Error setting kernel arguments" );
		return false;
	}
	errNum = clFlush(m_commandQueue);
	errNum = waitForEventAndRelease(&events[0]);

	errNum = clEnqueueReadBuffer( m_commandQueue, outputBuffer, CL_TRUE, 0, width * height * sizeof(float), pOutArray, 0, NULL, &events[1]);
	if(errNum != CL_SUCCESS)
	{
		return false;
	}
	errNum = clFlush(m_commandQueue);
	errNum = waitForEventAndRelease(&events[1]);

	clReleaseMemObject(inputBuffer);
	clReleaseMemObject(maskBuffer);
	clReleaseMemObject(outputBuffer);
	return true;
}

void SimpleConvolution::simpleConvolutionCPUReference(
	float  *output,
	const float  *input,
	const float  *mask,
	const cl_uint  width,
	const cl_uint  height,
	const cl_uint maskWidth,
	const cl_uint maskHeight)
{
	cl_uint vstep = (maskWidth  - 1) / 2;
    cl_uint hstep = (maskHeight - 1) / 2;

    for(cl_uint x = 0; x < width; x++)
        for(cl_uint y = 0; y < height; y++)
        {
            cl_uint left    = (x           <  vstep) ? 0         : (x - vstep);
            cl_uint right   = ((x + vstep) >= width) ? width - 1 : (x + vstep);
            cl_uint top     = (y           <  hstep) ? 0         : (y - hstep);
            cl_uint bottom  = ((y + hstep) >= height)? height - 1: (y + hstep);

            cl_float sumFX = 0;

            for(cl_uint i = left; i <= right; ++i)
                for(cl_uint j = top ; j <= bottom; ++j)
                {
                    cl_uint maskIndex = (j - (y - hstep)) * maskWidth  + (i - (x - vstep));
                    cl_uint index     = j                 * width      + i;

                    sumFX += ((float)input[index] * mask[maskIndex]);
                }
            sumFX += 0.5f;
            output[y*width + x] = float(sumFX);
        }

}

void SimpleConvolution::Destroy(){
	if(m_kernel != 0){
		clReleaseKernel( m_kernel );
		m_kernel = 0;
	}	
}

int SimpleConvolution::verifyResults(){
	float* verificationOutput = (float *) malloc(width * height * sizeof( float ));
    CHECK_ALLOCATION(verificationOutput,
                        "Failed to allocate host memory. (verificationOutput)");

    cl_uint2 inputDimensions = {width    , height};
    cl_uint2 maskDimensions  = {maskWidth, maskHeight};

    simpleConvolutionCPUReference(verificationOutput, input, mask, width, height,
                                    maskWidth, maskHeight);

    if(memcmp(output, verificationOutput, height*width*sizeof( float )) == 0)
    {
        std::cout<<"Passed!\n" << std::endl;
        return 0;
    }
    else
    {
        std::cout<<"Failed\n" << std::endl;
        return 1;
    }
}

