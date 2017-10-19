#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<list>
#include "headers/record.h"
#include "headers/util.h"
using namespace std;

int n;
int r;
int e;
int globalExcutionOrder;

int main(int argc, char* argv[]) {
	if(argc != 4) {
		printf("command : ./run N R E\n");
		exit(1);
	}

	n = atoi(argv[1]);
	r = atoi(argv[2]);
	e = atoi(argv[3]);
	globalExcutionOrder = 0;

/*
	LinkedList* lockTableList = new LinkedList[n];

	for(int i=0;i<n;i++) {
		lockTableList[i].setListId(i);
	}

	node* node1 = createNewNode(69);
	lockTableList[0].addNodeToHead(node1);

	printf("node thread id : %d\n", (lockTableList[0].getHead())->threadNum);*/

	Record* record = new Record[r];
	for(int i=0;i<r;i++) {
		record[i].initRecord(i, 100);
	}
	logLine("before push back");
	node* newNode = new node;
	createNewNode(newNode, 0, true);
	record[0].pushBackLockList(newNode);
	logLine("after push back");

	LinkedList* ll = record[0].getLockList();
	logLine("get lock list");
	cout << ll->getHead()->threadNum;


	return 0;
}


