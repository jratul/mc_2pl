#ifndef THREAD
#define THREAD
#include<pthread.h>
#include "headers/util.h"
#include "headers/thread.h"
#include "headers/rwlock.h"

struct threadParam {
	long threadNum;
	int maxRecordNum;
};

void* threadFunction(void* arg);


#endif
