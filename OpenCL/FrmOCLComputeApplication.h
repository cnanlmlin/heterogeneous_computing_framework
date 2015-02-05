#ifndef _FRM_OCL_COMPUTE_APPLICATION_H_
#define _FRM_OCL_COMPUTE_APPLICATION_H_

#include <CL/cl.h>

class CFrmComputeApplication_OCL
{
public:
    CFrmComputeApplication_OCL();
    virtual ~CFrmComputeApplication_OCL();

    cl_context getOCLContext(){ return m_context; }
    cl_device_id* getOCLDevice(){ return m_devices; }
    cl_command_queue getOCLCommandQueue(){ return m_commandQueue; }

    bool CreateOpenCLContext(cl_device_type deviceType);
    void DestroyOpenCLContext();


public:

    cl_platform_id m_platform;

    cl_context    m_context;

    cl_device_id *m_devices;

    int      m_deviceCount;
    
    cl_command_queue m_commandQueue;
};


#endif // _FRM_OCL_COMPUTE_APPLICATION_H_
