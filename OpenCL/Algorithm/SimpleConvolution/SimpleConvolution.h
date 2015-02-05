#ifndef _SIMPLECONVOLUTION_H
#define _SIMPLECONVOLUTION_H

#include "../../framework/OpenCL/FrmOCLUtils.h"
#include "../../framework/FrmUtils.h"

class SimpleConvolution
{
public:

	SimpleConvolution(int nWidth, int nHeight, int mWidth, int mHeight);
	virtual ~SimpleConvolution();

	bool Initialize( cl_context context, cl_device_id device, cl_command_queue commandQueue );

	bool runCLKernels( const float* pInArray, const float* pMaskArray, float* pOutArray);

	void simpleConvolutionCPUReference(
		float  *output,
		const float  *input,
		const float  *mask,
		const cl_uint  width,
		const cl_uint  height,
		const cl_uint maskWidth,
		const cl_uint maskHeight);

	void Destroy();

	int verifyResults();

private:

	cl_context m_context;

	cl_device_id m_device;

	cl_command_queue m_commandQueue;

	cl_kernel m_kernel;

	cl_int width, height;
	cl_uint maskWidth, maskHeight;
	float *input;
	float *output;
	float *mask;

	cl_mem inputBuffer;
	cl_mem outputBuffer;
	cl_mem maskBuffer;

	int iterations;

};

#endif // _SIMPLECONVOLUTION_H
