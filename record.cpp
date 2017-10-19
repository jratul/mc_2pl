#include "headers/record.h"

void Record::initRecord(int recordId, long recordVal) {
	this->recordId = recordId;
	this->recordVal = recordVal;
}
int Record::getRecordId(void) { return recordId; }
long Record::getRecordVal(void) { return recordVal;}
LinkedList* Record::getLockList(void) { return &lockList; }
void Record::setRecordId(int recordId) { this->recordId = recordId; }
void Record::setRecordVal(long recordVal) { this->recordVal = recordVal; }
void Record::pushBackLockList(node* newNode) {
	//const ListItem* listItem = new ListItem(threadId, isWrite);
	//lockList.push_back(listItem);
	this->lockList.addNodeToTail(newNode);
}