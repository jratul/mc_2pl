#ifndef THREAD
#define THREAD
#include<pthread.h>
#include "util.h"
#include "rwlock.h"

struct threadParam {
	long threadNum;
	int maxRecordNum;
};

void* threadFunction(void* arg);
bool checkCycle(int recordNumIdx, int* randomNumbers, long threadNum);
void delAllNodeFromThread(int* randomNumbers, long threadNum);
bool isFromSameThread(node* node1, node* node2);
bool checkProcess(node* cursor, long targetThreadNum, set<long> tidRecord);
#endif
