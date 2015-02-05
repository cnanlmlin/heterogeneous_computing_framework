#ifndef _FRM_PLATFORM_H_
#define _FRM_PLATFORM_H_


#include <jni.h>
#include <errno.h>
#include <stdio.h>
#include <android/sensor.h>
#include <android/log.h>
#include <android_native_app_glue.h>

//if(_OGLES3)


//linux - Network
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

// Linux - Threads
#include <pthread.h>

// Linux - semaphores
#include <semaphore.h>

#define LOGI(...) ((void)__android_log_print(ANDROID_LOG_INFO, "GPUCompute-framework", __VA_ARGS__))
#define LOGW(...) ((void)__android_log_print(ANDROID_LOG_WARN, "GPUCompute-framework", __VA_ARGS__))
#define LOGE(...) ((void)__android_log_print(ANDROID_LOG_ERROR, "GPUCompute-framework", __VA_ARGS__))

#define PLATFORM ANDROID

typedef unsigned char      BYTE;


#endif
