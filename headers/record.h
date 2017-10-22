#ifndef RECORD
#define RECORD
#include<list>
#include<iostream>
#include"linked_list.h"
using namespace std;

/*
class ListItem {
private:
	int threadId;
	bool isWrite;
public:
	ListItem(int threadId_, bool isWrite_)
	: threadId(threadId_),
	isWrite(isWrite_) 
	{};
	~ListItem();

};
*/

class Record {
private:
	int recordId;
	long long recordVal;
	LinkedList* lockList;
public:
	void initRecord(int recordId, long long recordVal);

	int getRecordId(void);
	long long getRecordVal(void);
	LinkedList* getLockList(void);
	void setRecordId(int recordId);
	void setRecordVal(long long recordVal);
	void pushBackLockList(node* newNode);

};

#endif