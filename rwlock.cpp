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
	while(true) {
		if(cnt == 1000) {
			cout << "rwunlock : " << headNode->threadNum << ", " << targetTempNode->threadNum << " // " << headNode->isWrite << ", " << targetTempNode->isWrite << endl;
			printLockList(int recordNum, long threadNum, bool isWrite);
		}
		if(isSameNode(headNode, targetTempNode)) {
			break;
		}
		cnt++;
	}

	(record[recordNum].getLockList())->delNodeFromHead();

	delete targetTempNode;
}

void printLockList(int recordNum, long threadNum, bool isWrite) {
	cout << "this is lock list of (" << recordNum << " " << threadNum << " " << isWrite << endl;
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

