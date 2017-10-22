#include "headers/rwlock.h"

bool isSameNode(node* node1, node* node2) {
	if((node1->threadNum == node2->threadNum) && (node1->isWrite == node2->isWrite)) {
		return true;
	} else {
		return false;
	}
}

void rwLock(int recordNum, long threadNum, bool isWrite) {
	node* headNode = (record[recordNum].getLockList())->getHead();
	node* targetTempNode = new node;
	targetTempNode->threadNum = threadNum;
	targetTempNode->isWrite = isWrite;

	int cnt = 0;
	while(true) {
		if(cnt == 1000) {
			cout << "cnt 1000" << endl;
			printLockList(recordNum, threadNum, isWrite);
			delNodeForce(threadNum);
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
}

void rwUnlock(int recordNum, long threadNum, bool isWrite) {
	node* headNode = (record[recordNum].getLockList())->getHead();
	node* targetTempNode = new node;
	targetTempNode->threadNum = threadNum;
	targetTempNode->isWrite = isWrite;
	int cnt = 0;
	bool allRead = false;

	while(true) {
		if(cnt == 1000) {
			delNodeForce(threadNum);
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

	for(int i=0;i<n*CHOOSING_RECORD_NUM;i++) {
		recordArr[i] = -1;
		threadArr[i] = -1;
	}

	for(int i=0;i<r;i++) {
		if((record[i].getLockList())->getHead() != NULL) {
			recordArr[cnt] = i;
			threadArr[cnt] = (record[i].getLockList())->getHead()->threadNum;
			cnt++;
		}
	}

	int* nodeCnt = new int[n];
	for(int i=0;i<n*CHOOSING_RECORD_NUM;i++) {
		nodeCnt[threadArr[i]]++;
	}

	int smallest = -1;
	long smallestTid = 0;
	for(int i=0;i<n;i++) {
		if(nodeCnt[i] < smallest || smallest == -1) {
			smallest = nodeCnt[i];
			smallestTid = i;
		}
	}

	for(int i=0;i<r;i++) {
		if((record[i].getLockList())->getHead() != NULL) {
			if((record[i].getLockList())->getHead()->threadNum == smallestTid) {
				cout << "del head!" << endl;
				(record[i].getLockList())->delNodeFromHead();
			}
		}
	}
}












