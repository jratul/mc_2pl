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
		if(cursor == head) {
			cursor = head->next;
		} 
		head = head->next;
		head->pre = NULL;
	} else {
		if(head == tail) {
			tail = NULL;
		}
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
		if(head == tail) {
			head = NULL;
		}
		tail = NULL;
	}
}

void LinkedList::delNodeFromCursor(node *targetNode) {
	if(targetNode == head) {
		delNodeFromHead();
	} else if(targetNode == tail) {
		delNodeFromTail();
	} else {
		targetNode->pre->next = targetNode->next;
		targetNode->next->pre = targetNode->pre;
		targetNode = NULL;
	}
}




