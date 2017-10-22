#include "headers/thread.h"

void* threadFunction(void* arg) {
	threadParam * tp = (threadParam*)arg;
	long tid = tp->threadNum;
	int maxRecordNum = tp->maxRecordNum;

	while(globalExecutionOrder < e) {
		int* randomNumbers = new int[CHOOSING_THREAD_NUM];
		long i,j,k;
		long iTemp, jTemp, kTemp;
		node* newNode = new node[CHOOSING_THREAD_NUM];

		for(int idx=0;idx<CHOOSING_THREAD_NUM;idx++) {
			randomNumbers[idx] = -1;
		}

		randomNumbers = getRandomNumbers(randomNumbers, maxRecordNum);

		pthread_mutex_lock(&globalMutex);
		createNewNode(&newNode[0], tid, false);
		record[randomNumbers[0]].pushBackLockList(&newNode[0]);
		rwLock(randomNumbers[0], tid, false);
		pthread_mutex_unlock(&globalMutex);
		iTemp = record[randomNumbers[0]].getRecordVal();
		i = iTemp;

		pthread_mutex_lock(&globalMutex);
		createNewNode(&newNode[1], tid, true);
		record[randomNumbers[1]].pushBackLockList(&newNode[1]);
		rwLock(randomNumbers[1], tid, true);
		pthread_mutex_unlock(&globalMutex);
		jTemp = record[randomNumbers[1]].getRecordVal();
		j = i + 1;
		cout << "i : " << i << " j : " << j << endl;

		pthread_mutex_lock(&globalMutex);
		createNewNode(&newNode[2], tid, true);
		record[randomNumbers[2]].pushBackLockList(&newNode[2]);
		rwLock(randomNumbers[2], tid, true);
		pthread_mutex_unlock(&globalMutex);
		kTemp = record[randomNumbers[2]].getRecordVal();
		k = kTemp - i;

		pthread_mutex_lock(&globalMutex);
		record[randomNumbers[0]].setRecordVal(i);
		record[randomNumbers[1]].setRecordVal(j);
		record[randomNumbers[2]].setRecordVal(k);
		rwUnlock(randomNumbers[0], tid, false);
		rwUnlock(randomNumbers[1], tid, true);
		rwUnlock(randomNumbers[2], tid, true);
		globalExecutionOrder++;

		if(globalExecutionOrder > e) {
			record[randomNumbers[0]].setRecordVal(iTemp);
			record[randomNumbers[1]].setRecordVal(jTemp);
			record[randomNumbers[2]].setRecordVal(kTemp);
		} else {
			printCommitLog(globalExecutionOrder, randomNumbers, i, j, k, tid);
		}

		pthread_mutex_unlock(&globalMutex);

		delete [] randomNumbers;
		delete [] newNode;
	}

	return NULL;
}