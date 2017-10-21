#ifndef UTIL
#define UTIL
#include<iostream>
#include<string>
#include<pthread.h>
#define CHOOSING_THREAD_NUM 3
using namespace std;

int n;
int r;
int e;
int globalExcutionOrder;
pthread_mutex_t globalMutex = PTHREAD_MUTEX_INITIALIZER;
Record* record;

void logLine(string logData);
int* getRandomNumbers(int* randomNumbers, int maxRecordNum);
void printCommitLog(int commitId, int* idx, long valI, long valJ, long valK);

#endif