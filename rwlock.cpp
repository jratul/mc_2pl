#include "headers/rwlock.h"

bool isSameNode(node* node1, node* node2) {
	if((node1->threadNum == node2->threadNum) && (node1->isWrite == node2->isWrite)) {
		return true;
	} else {
		return false;
	}
}

bool rwLock(int recordNum, long threadNum, bool isWrite) {
	node* headNode = (record[recordNum].getLockList())->getHead();
	node* targetTempNode = new node;
	targetTempNode->threadNum = threadNum;
	targetTempNode->isWrite = isWrite;

	int cnt = 0;
	while(true) {
		if(cnt == 100) {
			printLockList(recordNum, threadNum, isWrite);
			delNodeForce(threadNum);
			return false;
		}
		if(globalExecutionOrder > e) {
			break;
		}
		if(isSameNode(headNode, targetTempNode)) {
			break;
		}

		if(!isWrite) {
			node* cursor = (record[recordNum].getLockList())->getHead();
			bool allRead = true;
			while(cursor != NULL) {
				if(isSameNode(cursor, targetTempNode)) {
					break;
				}

				if(cursor->isWrite) {
					allRead = false;
					break;
				}

				cursor = cursor->next;
			}

			if(allRead) {
				break;
			}
		}
		cnt++;
	}

	delete targetTempNode;

	return true;
}

void rwUnlock(int recordNum, long threadNum, bool isWrite) {
	node* headNode = (record[recordNum].getLockList())->getHead();
	node* targetTempNode = new node;
	targetTempNode->threadNum = threadNum;
	targetTempNode->isWrite = isWrite;
	int cnt = 0;
	bool allRead = false;

	while(true) {
		if(cnt == 100) {
			delNodeForce(threadNum);
			return false;
			//cout << "rwunlock record[" << recordNum << "] : " << headNode->threadNum << ", " << targetTempNode->threadNum << " // " << headNode->isWrite << ", " << targetTempNode->isWrite << endl;
			//printLockList(recordNum,threadNum,isWrite);
		}
		if(isSameNode(headNode, targetTempNode)) {
			break;
		}

		if(globalExecutionOrder > e) {
			break;
		}

		if(!isWrite) {
			node* cursor = (record[recordNum].getLockList())->getHead();
			allRead = true;
			while(cursor != NULL) {
				if(isSameNode(cursor, targetTempNode)) {
					break;
				}

				if(cursor->isWrite) {
					allRead = false;
					break;
				}

				cursor = cursor->next;
			}

			if(allRead) {
				break;
			}
		}
		cnt++;
	}

	if(allRead) {
		node* cursor = (record[recordNum].getLockList())->getHead();
		while(cursor != NULL) {
			if(isSameNode(cursor, targetTempNode)) {
				(record[recordNum].getLockList())->delNodeFromCursor(cursor);
				break;
			}
			cursor = cursor->next;
		}
	} else {
		(record[recordNum].getLockList())->delNodeFromHead();
	}

	delete targetTempNode;

	return true;
}

void printLockList(int recordNum, long threadNum, bool isWrite) {
	cout << "this is lock list of (" << recordNum << " " << threadNum << " " << isWrite << ")" << endl;
	for(int i=0;i<r;i++) {
		if((record[i].getLockList())->getHead() != NULL) {
			node* cursor = (record[i].getLockList())->getHead();
			cout << "record[" << i << "] : ";
			while(cursor != NULL) {
				cout << "(" << cursor->threadNum << ", " << cursor->isWrite << ")";
				if(cursor->next != NULL) {
					cout << " -> ";
				}
				cursor = cursor->next;
			}

			cout << endl << endl;
		}
	}
}

void delNodeForce(long threadNum) {
	cout << "delnodeforce" << endl;
	int* recordArr = new int[n*CHOOSING_RECORD_NUM];
	long* threadArr = new long[n*CHOOSING_RECORD_NUM];
	int cnt = 0;

	cout << "delnodeforce 2" << endl;
	for(int i=0;i<n*CHOOSING_RECORD_NUM;i++) {
		recordArr[i] = -1;
		threadArr[i] = -1;
	}

	cout << "delnodeforce 3" << endl;
	for(int i=0;i<r;i++) {
		if((record[i].getLockList())->getHead() != NULL) {
			recordArr[cnt] = i;
			threadArr[cnt] = (record[i].getLockList())->getHead()->threadNum;
			cnt++;
		}
	}
	cout << "delnodeforce 4" << endl;
	int* nodeCnt = new int[n];
	for(int i=0;i<n*CHOOSING_RECORD_NUM;i++) {
		nodeCnt[threadArr[i]]++;
	}
	cout << "delnodeforce 5" << endl;
	int smallest = -1;
	long smallestTid = 0;
	for(int i=0;i<n;i++) {
		if((nodeCnt[i] < smallest || smallest == -1) && nodeCnt[i] > 0) {
			smallest = nodeCnt[i];
			smallestTid = i;
		}
	}
	cout << "smallestTid : " << smallestTid << endl;

	for(int i=0;i<r;i++) {
		if((record[i].getLockList())->getHead() != NULL) {
			if((record[i].getLockList())->getHead()->threadNum == smallestTid) {
				cout << "del head!" << endl;
				pthread_mutex_lock(&globalMutex);
				(record[i].getLockList())->delNodeFromHead();
				pthread_mutex_unlock(&globalMutex);
			}
		}
	}

	delete [] threadArr;
	delete [] recordArr;

}












