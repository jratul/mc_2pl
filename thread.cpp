#include <fstream>
#include "headers/thread.h"
using namespace std;

void* threadFunction(void* arg) {
	threadParam * tp = (threadParam*)arg;
	long tid = tp->threadNum;
	int maxRecordNum = tp->maxRecordNum;

	string fileName = "thread.txt";
	fileName.insert(6, to_string(tid + 1));
	ofstream output(fileName);
	output.close();

	while(globalExecutionOrder < e) {
		int* randomNumbers = new int[CHOOSING_THREAD_NUM];
		long long i,j,k;
		long long iTemp, jTemp, kTemp;
		node* newNode = new node[CHOOSING_THREAD_NUM];

		for(int idx=0;idx<CHOOSING_THREAD_NUM;idx++) {
			randomNumbers[idx] = -1;
		}

		randomNumbers = getRandomNumbers(randomNumbers, maxRecordNum);

		pthread_mutex_lock(&globalMutex);
		cout << "thread " << tid << " first start" << endl;
		createNewNode(&newNode[0], tid, false);
		record[randomNumbers[0]].pushBackLockList(&newNode[0]);
		printLockList(randomNumbers[0], tid, false);
		cout << "thread " << tid << " first end" << endl;
		pthread_mutex_unlock(&globalMutex);
		rwLock(randomNumbers[0], tid, false);
		
		
		
		iTemp = record[randomNumbers[0]].getRecordVal();
		i = iTemp;
		
	
		pthread_mutex_lock(&globalMutex);
		cout << "thread " << tid << " second start" << endl;
		createNewNode(&newNode[1], tid, true);
		record[randomNumbers[1]].pushBackLockList(&newNode[1]);
		printLockList(randomNumbers[1], tid, true);
		cout << "thread " << tid << " second end" << endl;
		if(checkCycle(1, randomNumbers, tid)) {
			pthread_mutex_unlock(&globalMutex);
			continue;
		}
		pthread_mutex_unlock(&globalMutex);
		rwLock(randomNumbers[1], tid, true);
		
		printLockList(randomNumbers[1], tid, true);
		
		jTemp = record[randomNumbers[1]].getRecordVal();
		j = jTemp + i + 1;
		
		

		
		pthread_mutex_lock(&globalMutex);
		cout << "thread " << tid << " third start" << endl;
		createNewNode(&newNode[2], tid, true);
		record[randomNumbers[2]].pushBackLockList(&newNode[2]);
		printLockList(randomNumbers[1], tid, true);
		cout << "thread " << tid << " third end" << endl;
		if(checkCycle(2, randomNumbers, tid)) {
			pthread_mutex_unlock(&globalMutex);
			continue;
		}
		pthread_mutex_unlock(&globalMutex);
		rwLock(randomNumbers[2], tid, true);
		//pthread_mutex_unlock(&globalMutex);	
		printLockList(randomNumbers[2], tid, true);
		
		kTemp = record[randomNumbers[2]].getRecordVal();
		k = kTemp - i;
		
		

		
		pthread_mutex_lock(&globalMutex);
		cout << "thread " << tid << " last start" << endl;
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

		cout << "thread " << tid << " last end" << endl;
		pthread_mutex_unlock(&globalMutex);
		

		delete [] randomNumbers;
		delete [] newNode;
	}

	return NULL;
}

bool checkCycle(int recordNumIdx, int* randomNumbers, long threadNum) {
	node* cursor = (record[randomNumbers[recordNumIdx]].getLockList())->getTail();
	node* head = (record[randomNumbers[recordNumIdx]].getLockList())->getHead();
	
	long long headTid = head->threadNum;

	int checkIdx = recordNumIdx - 1;

	while(checkIdx >= 0) {
		if((record[randomNumbers[checkIdx]].getLockList())->getTail()->threadNum == headTid) {
			return true;
		}
	}

	return false;
}












