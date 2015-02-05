#ifndef _FRM_PROGRAM_CACHE_H_
#define _FRM_PROGRAM_CACHE_H_

#include <map>
#include <iostream>
#include <sstream>
#include <CL/cl.h>
#include "FrmProgramEntry.h"

using namespace std;

class ProgramCache
{
protected:
	ProgramCache();
	~ProgramCache();
	static ProgramCache *_programCache;

	class CacheGarbo
	{
	public:
		~CacheGarbo(){
			if(NULL != _programCache)
				delete ProgramCache::_programCache;
		}
	};
	static CacheGarbo _cacheGarbo;

public:
	static ProgramCache *getProgramCache();

	cl_program getProgram(const cl_context ctx,  const cl_device_id* device, cl_uint deviceCount, const ProgramEntry* source,
		const char *build_options);

	void releaseProgram();
protected:
	cl_program progLookup(const string& srcsign);

	void addProgram(const string& srcsign, cl_program program);

	std::map <string, cl_program> codeCache;
	unsigned int cacheSize;
	//static Mutex mutexFiles;
	//static Mutex mutexCache;
};

#endif
