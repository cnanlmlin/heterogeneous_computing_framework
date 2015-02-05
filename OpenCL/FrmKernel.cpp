#include "../FrmUtils.h"
#include "FrmKernel.h"
#include "FrmProgramCache.h"

#define PRIME_TIME_DURATION 250

bool FrmGetOrBuildComputeProgramFromFile(const ProgramEntry* ProgramSource,
                                     cl_program* pProgram,
                                     cl_context context,
                                     cl_device_id* pDevices,
                                     cl_uint deviceCount,
                                     const char* options )
{
    cl_program program = ProgramCache::getProgramCache()->getProgram(context, pDevices, deviceCount, ProgramSource, options);
	
    *pProgram = program;
    return true;
}

bool FrmPrimeGPU( cl_command_queue commandQueue, cl_kernel kernel,
                  cl_uint workDim, const size_t *globalWorkSize,
                  const size_t *localWorkSize)
{
    cl_int errNum;
    double elapsed_time = 0;

    while (elapsed_time < PRIME_TIME_DURATION) {
        CFrmTimer m_Timer;
        m_Timer.Reset();
        m_Timer.Start();

        errNum = clEnqueueNDRangeKernel( commandQueue, kernel, workDim, NULL,
                                    globalWorkSize, localWorkSize, 0, NULL, NULL );
        if( errNum != CL_SUCCESS )
        {
            FrmLogMessage( "Error queueing kernel for execution.");
            return false;
        }
        clFinish(commandQueue);

        m_Timer.Stop();
        elapsed_time += m_Timer.GetTime() * 1000;
    }
    return true;
}

