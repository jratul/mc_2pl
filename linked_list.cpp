#include<iostream>
#include"headers/linked_list.h"
using namespace std;

void createNewNode(node* newNode, int threadNum, bool isWrite) {
	newNode->threadNum = threadNum;
	newNode->isWrite = isWrite;
	newNode->next = NULL;
	newNode->pre = NULL;
}

LinkedList::LinkedList() {
	listId = 0;
	head = NULL;
	tail = NULL;
	cursor = NULL;
}

LinkedList::LinkedList(int listId) {
	this->listId = listId;
	head = NULL;
	tail = NULL;
	cursor = NULL;
}

int LinkedList::getListId(void) { return listId; }
node *LinkedList::getHead(void) { return head; }
node *LinkedList::getTail(void) { return tail; }
node *LinkedList::getCursor(void) { return cursor; }

void LinkedList::setListId(int listId) { this->listId = listId; }
void LinkedList::setHead(node *head) { this->head = head; }
void LinkedList::setTail(node *tail) { this->tail = tail; }
void LinkedList::moveCursorToNext(void) {
	if(cursor != NULL && cursor->next != NULL) {
		cursor = cursor->next;
	}
}

void LinkedList::moveCursorToPre(void) {
	if(cursor != NULL && cursor->pre != NULL) {
		cursor = cursor->pre;
	}
}

void LinkedList::addNodeToHead(node *newNode) {
	cout << "add node to head" << endl;
	if(head != NULL) {
		newNode->next = head;
		head->pre = newNode;
	} else {
		cursor = newNode;
	}
	head = newNode;

	if(tail == NULL) {
		tail = newNode;
	}
}

void LinkedList::addNodeToTail(node *newNode) {
	cout << "add node to tail" << endl;
	if(tail != NULL) {
		tail->next = newNode;
		newNode->pre = tail;
	} else {
		cursor = newNode;
	}
	tail = newNode;

	if(head == NULL) {
		head = newNode;
	}
}

void LinkedList::delNodeFromHead(void) {
	if(head->next != NULL) {
		cout << "del node : next is not null" << endl;
		if(cursor == head) {
			cursor = head->next;
		} 
		head = head->next;
		head->pre = NULL;
	} else {
		cout << "delete node" << endl;
		head->next = NULL;
		head->pre = NULL;
		head = NULL;
	}
}

void LinkedList::delNodeFromTail(void) {
	node* temp = tail;
	if(tail->pre != NULL) {
		if(cursor == tail) {
			cursor = tail->pre;
		}
		tail = tail->pre;
		tail->next = NULL;
	} else {
		tail->next = NULL;
		tail->pre = NULL;
		tail = NULL;
	}
}




