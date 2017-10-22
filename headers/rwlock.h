#ifndef RWLOCK
#define RWLOCK
#include "util.h"

bool isSameNode(node* node1, node* node2);
void rwLock(int recordNum, long threadNum, bool isWrite);
void rwUnlock(int recordNum, long threadNum, bool isWrite);
void printLockList();

#endif