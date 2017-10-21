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
	cout << "after head node" << endl;
	node* targetTempNode = new node;
	targetTempNode->threadNum = threadNum;
	targetTempNode->isWrite = isWrite;
	while(true) {
		cout << "rwlock while" << endl;
		if(isSameNode(headNode, targetTempNode)) {
			break;
		}
		cout << "rwlock while after issamenode" << endl;

		if(!isWrite) {
			cout << "rwlock while if" << endl;
			node* cursor = (record[recordNum].getLockList())->getHead();
			bool allRead = true;
			while(cursor != NULL) {
				cout << "rwlock while2" << endl;
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

	cout << "rwlock end" << endl;

	delete targetTempNode;
	//delete headNode;

	cout << "rwlock after delete" << endl;
}

void rwUnlock(int recordNum, long threadNum, bool isWrite) {
	node* headNode = (record[recordNum].getLockList())->getHead();
	node* targetTempNode = new node;
	targetTempNode->threadNum = threadNum;
	targetTempNode->isWrite = isWrite;
	while(true) {
		if(isSameNode(headNode, targetTempNode)) {
			(record[recordNum].getLockList())->delNodeFromHead();
			break;
		}
	}

	delete targetTempNode;
	//delete headNode;
}

