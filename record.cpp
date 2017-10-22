#include "headers/record.h"

void Record::initRecord(int recordId, long long recordVal) {
	this->recordId = recordId;
	this->recordVal = recordVal;
	lockList = new LinkedList();
}
int Record::getRecordId(void) { return recordId; }
long long Record::getRecordVal(void) { return recordVal;}
LinkedList* Record::getLockList(void) { return lockList; }
void Record::setRecordId(int recordId) { this->recordId = recordId; }
void Record::setRecordVal(long long recordVal) { this->recordVal = recordVal; }
void Record::pushBackLockList(node* newNode) {
	lockList->addNodeToTail(newNode);
}