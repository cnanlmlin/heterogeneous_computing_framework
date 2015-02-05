#ifndef _FRM_KERNEL_H_
#define _FRM_KERNEL_H_

#include <CL/cl.h>
#include "FrmProgramEntry.h"

bool FrmGetOrBuildComputeProgramFromFile(const ProgramEntry* ProgramSource,
                                     cl_program *pProgram,
                                     cl_context context,
                                     cl_device_id* pDevices,
                                     cl_uint deviceCount,
                                     const char* options = NULL );
bool FrmPrimeGPU( cl_command_queue commandQueue, cl_kernel kernel,
                  cl_uint workDim, const size_t *globalWorkSize,
                  const size_t *localWorkSize);

#endif // _FRM_KERNEL_H_
