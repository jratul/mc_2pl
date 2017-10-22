#ifndef UTIL
#define UTIL
#include<iostream>
#include<string>
#include<pthread.h>
#include "record.h"
#define CHOOSING_RECORD_NUM 3
using namespace std;

extern int n;
extern int r;
extern int e;
extern int globalExecutionOrder;
extern pthread_mutex_t globalMutex;
extern Record* record;

void logLine(string logData);
int* getRandomNumbers(int* randomNumbers, int maxRecordNum);
void printCommitLog(int commitId, int* idx, long long valI, long long valJ, long long valK, long threadNum);

#endif