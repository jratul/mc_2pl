#ifndef RWLOCK
#define RWLOCK
#include "util.h"

bool isSameNode(node* node1, node* node2);
bool rwLock(int recordNum, long threadNum, bool isWrite);
bool rwUnlock(int recordNum, long threadNum, bool isWrite);
void printLockList(int recordNum, long threadNum, bool isWrite);
void delNodeForce(long threadNum);

#endif