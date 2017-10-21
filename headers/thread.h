#ifndef THREAD
#define THREAD
#include<pthread.h>

struct threadParam {
	long threadNum;
	int maxRecordNum;
};

void* threadFunction(void* arg);


#endif
