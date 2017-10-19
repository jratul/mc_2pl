#include<iostream>
#include"headers/linked_list.h"
using namespace std;

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

void LinkedList::addNodeToHead(node *newNode) {
	if(head != NULL) {
		newNode->next = head;
		head->pre = newNode;
	} else {
		cursor = newNode;
	}
	head = newNode;
}

void LinkedList::addNodeToTail(node *newNode) {
	if(tail != NULL) {
		tail->next = newNode;
		newNode->pre = tail;
	} else {
		cursor = newNode;
	}
	tail = newNode;
}

void LinkedList::delNodeFromHead(void) {
	node* temp = head;
	if(head->next != NULL) {
		if(cursor == head) {
			cursor = head->next;
		} 
		head = head->next;
		head->pre = NULL;
	}
	
	delete temp;
}

void LinkedList::delNodeFromTail(void) {
	node* temp = tail;
	if(tail->pre != NULL) {
		if(cursor == tail) {
			cursor = tail->pre;
		}
		tail = tail->pre;
		tail->next = NULL;
	}

	delete temp;
}




