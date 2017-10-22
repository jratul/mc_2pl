#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<list>
#include<pthread.h>
#include "headers/record.h"
//#include "headers/util.h"
#include "headers/thread.h"
using namespace std;

int n = 0;
int r = 0;
int e = 0;
int globalExecutionOrder = 0;
pthread_mutex_t globalMutex = PTHREAD_MUTEX_INITIALIZER;
Record* record;

int main(int argc, char* argv[]) {
	srand((unsigned)time(NULL));

	if(argc != 4) {
		printf("command : ./run N R E\n");
		exit(1);
	}

	n = atoi(argv[1]);
	r = atoi(argv[2]);
	e = atoi(argv[3]);
	globalExecutionOrder = 0;

	pthread_t* threads;

/*
	LinkedList* lockTableList = new LinkedList[n];

	for(int i=0;i<n;i++) {
		lockTableList[i].setListId(i);
	}

	node* node1 = createNewNode(69);
	lockTableList[0].addNodeToHead(node1);

	printf("node thread id : %d\n", (lockTableList[0].getHead())->threadNum);*/

/*
	Record* record = new Record[r];
	for(int i=0;i<r;i++) {
		record[i].initRecord(i, 100);
	}
	node* newNode = new node;
	createNewNode(newNode, 0, true);
	record[0].pushBackLockList(newNode);

	LinkedList* ll = record[0].getLockList();
	cout << (ll->getHead())->threadNum;
*/

	record = new Record[r];
	for(int i=0;i<r;i++) {
		record[i].initRecord(i, 100);
	}

	threads = new pthread_t[n];
	threadParam tp;
	tp.threadNum = 0;
	tp.maxRecordNum = r;
	for(int i=0;i<n;i++) {
		if(pthread_create(&threads[i], 0, threadFunction, (void*)&tp) < 0) {
			printf("pthread_create error!\n");
			return 0;
		}
	}

	for(int i=0;i<n;i++) {
		pthread_join(threads[i],NULL);
	}
	delete [] threads;


	return 0;
}


