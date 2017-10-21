#include "headers/rwlock.h"

bool isSameNode(node* node1, node* node2) {
	if((node1->threadNum == node2->threadNum) && (node1->isWrite == node2->isWrite)) {
		return true;
	} else {
		return false;
	}
}

void rwLock(int recordNum, long threadNum, bool isWrite) {
	cout << "rwlock start" << endl;
	node* headNode = (record[recordNum].getLockList())->getHead();
	node* targetTempNode = new node;
	targetTempNode->threadNum = threadNum;
	targetTempNode->isWrite = isWrite;

	node* cursor = (record[recordNum].getLockList())->getHead();
	int cnt =0;
	while(cursor != NULL && cnt < 10) {
		cout << "cursor : (" << cursor->threadNum << ", " << cursor->isWrite << ")" << endl;
		cnt++;
		cursor = cursor->next;
	}

	while(true) {
		cout << "rwlock while start" << endl;
		cout << "rwlock - " << headNode->threadNum << ":" << targetTempNode->threadNum << ", " << headNode->isWrite << ":" << targetTempNode->isWrite <<endl;
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
		cout << "rwlock while end" << endl;
	}

	delete targetTempNode;
}

void rwUnlock(int recordNum, long threadNum, bool isWrite) {
	node* headNode = (record[recordNum].getLockList())->getHead();
	node* targetTempNode = new node;
	targetTempNode->threadNum = threadNum;
	targetTempNode->isWrite = isWrite;
	while(true) {
		if(isSameNode(headNode, targetTempNode)) {
			break;
		}
	}

	(record[recordNum].getLockList())->delNodeFromHead();

	delete targetTempNode;
}

