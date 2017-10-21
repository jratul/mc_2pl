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
	while(true) {
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
	}

	delete targetTempNode;
	delete headNode;

	return NULL;
}

void rwUnlock(int recordNum, long threadNum, bool isWrite) {
	node* headNode = (record[recordNum].getLockList())->getHead();
	node* targetTempNode = new node;
	targetTempNode->threadNum = threadNum;
	targetTempNode->isWrite = isWrite;
	while(true) {
		if(isSameNode(headNode, targetTempNode)) {
			(record[recordNum].getLockList)->delNodeFromHead();
			break;
		}
	}

	delete targetTempNode;
	delete headNode;

	return NULL;
}

