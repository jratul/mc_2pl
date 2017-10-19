#include<iostream>
#include<stdio.h>
#include<stdlib.h>
using namespace std;

int n;
int r;
int e;

/*
node* createNewNode(int threadNum) {
	node *newNode = new node;
	
	newNode->threadNum = threadNum;
	newNode->next = NULL;
	newNode->pre = NULL;

	return newNode;
}
*/

int main(int argc, char* argv[]) {
	if(argc != 4) {
		printf("command : ./run N R E\n");
		exit(1);
	}

	n = atoi(argv[1]);
	r = atoi(argv[2]);
	e = atoi(argv[3]);

/*
	LinkedList* lockTableList = new LinkedList[n];

	for(int i=0;i<n;i++) {
		lockTableList[i].setListId(i);
	}

	node* node1 = createNewNode(69);
	lockTableList[0].addNodeToHead(node1);

	printf("node thread id : %d\n", (lockTableList[0].getHead())->threadNum);*/

	return 0;
}


