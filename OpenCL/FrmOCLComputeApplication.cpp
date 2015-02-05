#include "FrmOCLComputeApplication.h"
#include "../FrmUtils.h"

CFrmComputeApplication_OCL::CFrmComputeApplication_OCL()
{
    m_platform = 0;
    m_context = 0;
    m_devices = 0;
    m_deviceCount = 0;

	m_commandQueue = 0;

	if (false == CreateOpenCLContext(CL_DEVICE_TYPE_GPU)) 
	{
		printf("CreateOpenCLContext Error!");
	}

}

CFrmComputeApplication_OCL::~CFrmComputeApplication_OCL()
{
    DestroyOpenCLContext();
}

bool CFrmComputeApplication_OCL::CreateOpenCLContext(cl_device_type deviceType)
{
    cl_int errNum;
    cl_uint numPlatforms = 0;
    cl_platform_id platformId;

    errNum = clGetPlatformIDs( 1, &platformId, &numPlatforms );
    if (errNum != CL_SUCCESS || numPlatforms <= 0)
    {
        FrmLogMessage("No OpenCL platforms found.");
        return false;
    }

    m_platform = platformId;

    cl_uint numDevices = 0;
    errNum = clGetDeviceIDs( platformId, deviceType, 0, NULL, &numDevices );
    if (errNum != CL_SUCCESS || numDevices <= 0)
    {
        FrmLogMessage("No matching OpenCL devices found.");
        return false;
    }

    char platformInfo[1024];
    char logMessage[2048];
    errNum = clGetPlatformInfo( platformId, CL_PLATFORM_VENDOR, sizeof(platformInfo), platformInfo, NULL );
    if (errNum != CL_SUCCESS)
    {
        FrmLogMessage("ERROR: getting platform info.");
        return false;
    }
    FrmSprintf( logMessage, sizeof(logMessage), "OpenCL Platform: %s\n", platformInfo );
    FrmLogMessage( logMessage );

    m_devices = new cl_device_id[numDevices];
    m_deviceCount = numDevices;
    errNum = clGetDeviceIDs( platformId, deviceType, numDevices, m_devices, NULL );
    if (errNum != CL_SUCCESS)
    {
        FrmLogMessage("Erorr getting OpenCL device(s).");
        return false;
    }    

    switch (deviceType)
    {
    case CL_DEVICE_TYPE_GPU:
        FrmLogMessage("Selected device: GPU\n");
        break;
    case CL_DEVICE_TYPE_CPU:
        FrmLogMessage("Selected device: CPU\n");
        break;
    case CL_DEVICE_TYPE_DEFAULT:
    default:
        FrmLogMessage("Selected device: DEFAULT\n");
        break;   
    }

    for (int i = 0; i < m_deviceCount; i++)
    {
        char deviceInfo[1024];
        errNum = clGetDeviceInfo( m_devices[i], CL_DEVICE_NAME, sizeof(deviceInfo), deviceInfo, NULL );
        if (errNum == CL_SUCCESS )
        {
            FrmSprintf( logMessage, sizeof(logMessage), "OpenCL Device Name (%d) : %s\n", i , deviceInfo );
            FrmLogMessage( logMessage );
        }
    }

    cl_context_properties contextProperties[] =
    {
        CL_CONTEXT_PLATFORM,
        (cl_context_properties)platformId,
        0
    };
    m_context = clCreateContext( contextProperties, m_deviceCount, m_devices, NULL, NULL, &errNum );
    if (errNum != CL_SUCCESS)
    {
        FrmLogMessage("Could not create OpenCL context.");
        return false;
    }

	m_commandQueue = clCreateCommandQueue( m_context, m_devices[0], CL_QUEUE_PROFILING_ENABLE, &errNum );
	if ( errNum != CL_SUCCESS )
	{
		FrmLogMessage( "Failed to create command queue" );
		return false;
	}

    return true;
}

void CFrmComputeApplication_OCL::DestroyOpenCLContext()
{
    if ( m_context != 0 )
    {
        clReleaseContext( m_context );
        m_context = 0;
    }

    if ( m_devices )
    {
        delete [] m_devices;
        m_devices = NULL;
    }

	if( m_commandQueue != 0 )
	{
		clReleaseCommandQueue( m_commandQueue );
		m_commandQueue = 0;
	}
}
