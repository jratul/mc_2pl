#define RWLOCK
#ifndef RWLOCK

bool isSameNode(node* node1, node* node2);
void rwLock(int recordNum, int threadNum, bool isWrite);
void rwUnlock(int recordNum, int threadNum, bool isWrite);

#endif