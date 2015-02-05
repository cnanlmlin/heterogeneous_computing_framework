#include "FrmOCLUtils.h"

const char* getOpenCLErrorCodeStr(std::string input)
{
	return "unknown error code";
}


int waitForEventAndRelease(cl_event *event)
{
	cl_int status = CL_SUCCESS;
	cl_int eventStatus = CL_QUEUED;
	while(eventStatus != CL_COMPLETE)
	{
		status = clGetEventInfo(
			*event,
			CL_EVENT_COMMAND_EXECUTION_STATUS,
			sizeof(cl_int),
			&eventStatus,
			NULL);
		CHECK_OPENCL_ERROR(status, "clGetEventEventInfo Failed with Error Code:");
	}
	status = clReleaseEvent(*event);
	CHECK_OPENCL_ERROR(status, "clReleaseEvent Failed with Error Code:");
	return 0;
}


