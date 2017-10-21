/*
#include "headers/util.h"
#include "headers/thread.h"
#include "headers/rwlock.h"
*/
#include "headers/thread.h"

/*
int n;
int r;
int e;
int globalExecutionOrder;
*/
//int globalExecutionOrder;

void* threadFunction(void* arg) {
	threadParam * tp = (threadParam*)arg;
	long tid = tp->threadNum;
	int maxRecordNum = tp->maxRecordNum;

	while(globalExecutionOrder < e) {
		int* randomNumbers = new int[CHOOSING_THREAD_NUM];
		long i,j,k;
		node* newNode = new node[CHOOSING_THREAD_NUM];

		randomNumbers = getRandomNumbers(randomNumbers, maxRecordNum);

		for(int idx=0;idx<3;idx++) {
			cout << randomNumbers[idx] << endl;
		}

		logLine("before first");
		pthread_mutex_lock(&globalMutex);
		createNewNode(&newNode[0], tid, false);
		record[randomNumbers[0]].pushBackLockList(&newNode[0]);
		rwLock(randomNumbers[0], tid, false);
		pthread_mutex_unlock(&globalMutex);
		i = record[randomNumbers[0]].getRecordVal();
		logLine("after first");

		logLine("before second");
		pthread_mutex_lock(&globalMutex);
		createNewNode(&newNode[1], tid, true);
		record[randomNumbers[1]].pushBackLockList(&newNode[1]);
		rwLock(randomNumbers[1], tid, true);
		pthread_mutex_unlock(&globalMutex);
		logLine("before assign j");
		j = i + record[randomNumbers[1]].getRecordVal();
		logLIne("after assign j");
		logLine("after second");

		logLine("before third");
		pthread_mutex_lock(&globalMutex);
		createNewNode(&newNode[2], tid, true);
		record[randomNumbers[2]].pushBackLockList(&newNode[2]);
		rwLock(randomNumbers[2], tid, true);
		pthread_mutex_unlock(&globalMutex);
		k = record[randomNumbers[2]].getRecordVal() - i;
		logLine("after third");

		logLine("before final");
		pthread_mutex_lock(&globalMutex);
		rwUnlock(randomNumbers[0], tid, false);
		rwUnlock(randomNumbers[1], tid, false);
		rwUnlock(randomNumbers[2], tid, false);
		globalExecutionOrder++;
		printCommitLog(globalExecutionOrder, randomNumbers, i, j, k);
		pthread_mutex_unlock(&globalMutex);
		logLine("after final");

		delete [] randomNumbers;
		delete [] newNode;
	}

	return NULL;
}