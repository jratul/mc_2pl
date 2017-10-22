#include <fstream>
#include "headers/thread.h"
#include "headers/linked_list.h"
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
		int* randomNumbers = new int[CHOOSING_RECORD_NUM];
		long long i,j,k;
		long long iTemp, jTemp, kTemp;
		node* newNode = new node[CHOOSING_RECORD_NUM];

		for(int idx=0;idx<CHOOSING_RECORD_NUM;idx++) {
			randomNumbers[idx] = -1;
		}

		randomNumbers = getRandomNumbers(randomNumbers, maxRecordNum);

		pthread_mutex_lock(&globalMutex);
		cout << "thread " << tid << " first start" << endl;
		createNewNode(&newNode[0], tid, false);
		record[randomNumbers[0]].pushBackLockList(&newNode[0]);
		printLockList(randomNumbers[0], tid, false);
		cout << "thread " << tid << " first end" << endl;
		//rwLock(randomNumbers[0], tid, false);
		pthread_mutex_unlock(&globalMutex);
		
		iTemp = record[randomNumbers[0]].getRecordVal();
		i = iTemp;
		
	
		pthread_mutex_lock(&globalMutex);
		cout << "thread " << tid << " second start" << endl;
		createNewNode(&newNode[1], tid, true);
		record[randomNumbers[1]].pushBackLockList(&newNode[1]);
		printLockList(randomNumbers[1], tid, true);
		cout << "thread " << tid << " second end" << endl;
		if(checkCycle(1, randomNumbers, tid)) {
			delAllNodeFromThread(randomNumbers, tid);
			pthread_mutex_unlock(&globalMutex);
			continue;
		}
		//rwLock(randomNumbers[1], tid, true);
		pthread_mutex_unlock(&globalMutex);
		
		
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
			delAllNodeFromThread(randomNumbers, tid);
			pthread_mutex_unlock(&globalMutex);
			continue;
		}
		//rwLock(randomNumbers[2], tid, true);
		
		pthread_mutex_unlock(&globalMutex);	
		printLockList(randomNumbers[2], tid, true);
		
		kTemp = record[randomNumbers[2]].getRecordVal();
		k = kTemp - i;

		rwLock(randomNumbers[0], tid, false);
		rwLock(randomNumbers[1], tid, true);
		rwLock(randomNumbers[2], tid, true);
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
			cout << "rollback" << endl;
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
	
	long headTid = head->threadNum;
	int checkIdx = recordNumIdx - 1;

	if(isFromSameThread(head,cursor)) {
		return false;
	}

/*
	set<long> tidRecord;
	tidRecord.insert(threadNum);
	return checkProcess(cursor, threadNum, tidRecord);
	*/

	for(int i=0;i<r;i++) {
		if((record[r].getLockList())->getTail() != NULL){
			node* cursor = (record[randomNumbers[recordNumIdx]].getLockList())->getTail();
			set<long> tidRecord;
			tidRecord.insert(cursor->threadNum);
			if(checkProcess(cursor, cursor->threadNum, tidRecord)) {
				return true;
			}
		}
	}

	return false;
}

bool checkProcess(node* cursor, long targetThreadNum, set<long> tidRecord) {
	cout << "checkProcess for " << targetThreadNum << endl;
	while(cursor->pre != NULL) {
		cursor = cursor->pre;

		set<long>::iterator iter;
		for(iter = tidRecord.begin(); iter!= tidRecord.end(); iter++) {
			cout << "tidRecord : " << *iter << endl;
			if(*iter == cursor->threadNum) {
				cout << "it's cycle" << endl;
				return true;
			}
		}

		cout << endl;
		tidRecord.insert(cursor->threadNum);
		cout << "insert " << cursor->threadNum << endl;
	}

	for(int i=0;i<r;i++) {
		cout << "in for" << endl;
		if((record[r].getLockList())->getTail() != NULL) {
			cout << "in if 1" << endl;
			if((record[r].getLockList())->getTail()->threadNum == cursor->threadNum &&
				(record[r].getLockList())->getTail()->threadNum != (record[r].getLockList())->getHead()->threadNum) {
				cout << "next thread num : " << cursor->threadNum << endl;
				if(checkProcess(cursor, targetThreadNum, tidRecord)) return true;
			}
		}
	}

	cout << "it's not cycle" << endl;
	return false;
}

void delAllNodeFromThread(int* randomNumbers, long threadNum) {
	for(int i=0;i<CHOOSING_RECORD_NUM;i++) {
		node* cursor = (record[randomNumbers[i]].getLockList())->getHead();

		while(cursor != NULL) {
			if(cursor->threadNum == threadNum) {
				(record[randomNumbers[i]].getLockList())->delNodeFromCursor(cursor);
				break;
			}
			cursor = cursor->next;
		}
	}
}

bool isFromSameThread(node* node1, node* node2) {
	if(node1->threadNum == node2->threadNum) {
		return true;
	} else {
		return false;
	}
}








