#include "FrmOCLUtils.h"
#include "FrmProgramCache.h"

//Mutex ProgramCache::mutexFiles;
//Mutex ProgramCache::mutexCache;

ProgramCache* ProgramCache::_programCache = NULL;
ProgramCache::CacheGarbo ProgramCache::_cacheGarbo;

ProgramCache* ProgramCache::getProgramCache()
{
	if (NULL == _programCache)
	{
		//AutoLock lock(getInitializationMutex());
		if (NULL == _programCache)
			_programCache = new ProgramCache();
	}
	return _programCache;
}

ProgramCache::ProgramCache()
{
	codeCache.clear();
	cacheSize = 0;
}

ProgramCache::~ProgramCache()
{
	releaseProgram();
	if (this == _programCache)
	{
		//AutoLock lock(getInitializationMutex());
		if (this == _programCache)
			_programCache = NULL;
	}
}

cl_program ProgramCache::progLookup(const string& srcsign)
{
	map<string, cl_program>::iterator iter;
	iter = codeCache.find(srcsign);
	if(iter != codeCache.end())
		return iter->second;
	else
		return NULL;
}

void ProgramCache::addProgram(const string& srcsign, cl_program program)
{
	if (!progLookup(srcsign))
	{
		clRetainProgram(program);
		codeCache.insert(map<string, cl_program>::value_type(srcsign, program));
	}
}

void ProgramCache::releaseProgram()
{
	map<string, cl_program>::iterator iter;
	for(iter = codeCache.begin(); iter != codeCache.end(); iter++)
	{
		clReleaseProgram(iter->second);		
	}
	codeCache.clear();
	cacheSize = 0;
}

cl_program getOrBuildProgram(const cl_context ctx, const cl_device_id* device, cl_uint deviceCount, const ProgramEntry* source, const char *build_options)
{
	cl_program program = NULL;
	cl_int errNum = 0;
	char logMsg[1024];
	//std::vector<char> binary;
	program = clCreateProgramWithSource(ctx, 1, (const char**)&source->programStr, NULL, &errNum);
	if( errNum != CL_SUCCESS || program == 0 )
	{
		sprintf( logMsg, sizeof(logMsg), "ERROR: failed to create program with source from file\n");
		FrmLogMessage( logMsg );
		return NULL;
	}
	//cl_device_id device = getClDeviceID(ctx);
	errNum = clBuildProgram(program, deviceCount, device, build_options/*NULL*/, NULL, NULL);
	if( errNum != CL_SUCCESS )
	{
		sprintf( logMsg, sizeof(logMsg), "ERROR: faild to build program with source from file\n");
		FrmLogMessage( logMsg );
		
		return NULL;
	}

	{
		cl_build_status buildStatus;
		errNum = clGetProgramBuildInfo( program, *device, CL_PROGRAM_BUILD_STATUS, sizeof(buildStatus), &buildStatus, NULL );
		if( errNum != CL_SUCCESS )
		{
			FrmLogMessage( "ERROR: Failed to get CL_PROGRAM_BUILD_STATUS\n" );
			clReleaseProgram( program );
			return NULL;
		}

		if (buildStatus != CL_BUILD_SUCCESS )
		{
			char *buildLog;
			size_t buildLogSize = 0;

			clGetProgramBuildInfo( program, *device, CL_PROGRAM_BUILD_LOG, 0, NULL, &buildLogSize );
			buildLog = new char[ buildLogSize ];

			clGetProgramBuildInfo( program, *device, CL_PROGRAM_BUILD_LOG, buildLogSize, buildLog, NULL);
			sprintf( logMsg, sizeof(logMsg), "ERROR: Building program '%s' (build_status: %d) \n:", source->programStr, buildStatus );
			FrmLogMessage( logMsg );
			FrmLogMessage( buildLog );
			delete [] buildLog;
			clReleaseProgram( program );
			return NULL;     
		}
	}
	return program;
}

cl_program ProgramCache::getProgram(const cl_context ctx, const cl_device_id* device, cl_uint deviceCount, const ProgramEntry* source,
	const char *build_options)
{
	std::stringstream src_sign;

	if (source->name)
	{
		src_sign << source->name;
		src_sign << ctx;
		if (NULL != build_options)
		{
			src_sign << "_" << build_options;
		}

		{
			//AutoLock lockCache(mutexCache);
			cl_program program = ProgramCache::getProgramCache()->progLookup(src_sign.str());
			if (!!program)
			{
				clRetainProgram(program);
				return program;
			}
		}
	}

	//AutoLock lockCache(mutexFiles);

	// second check
	if (source->name)
	{
		//AutoLock lockCache(mutexCache);
		cl_program program = ProgramCache::getProgramCache()->progLookup(src_sign.str());
		if (!!program)
		{
			clRetainProgram(program);
			return program;
		}
	}
	cl_program program = getOrBuildProgram(ctx, device, deviceCount, source, build_options);

	if (source->name)
	{
		//AutoLock lockCache(mutexCache);
		this->addProgram(src_sign.str(), program);
	}
	return program;
}
