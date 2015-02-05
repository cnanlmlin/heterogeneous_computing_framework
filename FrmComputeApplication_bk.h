#ifndef _FRM_COMPUTE_APPLICATION_H_
#define _FRM_COMPUTE_APPLICATION_H_

#include <CL/cl.h>

class CFrmComputeApplication
{
public:
    virtual bool Initialize() = 0;
    virtual void Destroy() = 0;

    bool RunTests() const { return m_bRunTests; }

    CFrmComputeApplication( const char* strName);
    virtual ~CFrmComputeApplication();

    bool CreateOpenCLContext(cl_device_type deviceType);
    void DestroyOpenCLContext();


public:

    cl_platform_id m_platform;

    cl_context    m_context;

    cl_device_id *m_devices;

    int      m_deviceCount;
    
    const char* m_strName;

    bool m_bRunTests;    
};

#endif // _FRM_COMPUTE_APPLICATION_H_
