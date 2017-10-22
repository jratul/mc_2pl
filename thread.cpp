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

		//cout << "thread " << tid << " first start" << endl;
		pthread_mutex_lock(&globalMutex);
		createNewNode(&newNode[0], tid, false);
		record[randomNumbers[0]].pushBackLockList(&newNode[0]);
		rwLock(randomNumbers[0], tid, false);
		pthread_mutex_unlock(&globalMutex);
		printLockList(randomNumbers[0], tid, false);
		
		iTemp = record[randomNumbers[0]].getRecordVal();
		i = iTemp;
		//cout << "thread " << tid << " first end" << endl;
		

		//cout << "thread " << tid << " second start" << endl;
		pthread_mutex_lock(&globalMutex);
		createNewNode(&newNode[1], tid, true);
		record[randomNumbers[1]].pushBackLockList(&newNode[1]);
		rwLock(randomNumbers[1], tid, true);
		pthread_mutex_unlock(&globalMutex);
		printLockList(randomNumbers[1], tid, true);
		
		jTemp = record[randomNumbers[1]].getRecordVal();
		j = jTemp + i + 1;
		//cout << "thread " << tid << " second end" << endl;
		

		//cout << "thread " << tid << " third start" << endl;
		pthread_mutex_lock(&globalMutex);
		createNewNode(&newNode[2], tid, true);
		record[randomNumbers[2]].pushBackLockList(&newNode[2]);
		rwLock(randomNumbers[2], tid, true);
		pthread_mutex_unlock(&globalMutex);	
		printLockList(randomNumbers[2], tid, true);
		
		kTemp = record[randomNumbers[2]].getRecordVal();
		k = kTemp - i;
		//cout << "thread " << tid << " third end" << endl;
		

		//cout << "thread " << tid << " last start" << endl;
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
		//cout << "thread " << tid << " last end" << endl;

		delete [] randomNumbers;
		delete [] newNode;
	}

	return NULL;
}