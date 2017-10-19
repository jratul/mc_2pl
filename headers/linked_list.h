#ifndef LINKED_LIST
#define LINKED_LIST

struct node {
	int threadNum;
	node* next;
	node* pre;
};

class LinkedList {	
private:
	int listId;
	node *head, *tail, *cursor;
public:		
	LinkedList();
	LinkedList(int listId);

	int getListId(void);
	node *getHead(void);
	node *getTail(void);
	node *getCursor(void);
	
	void setListId(int listId);
	void setHead(node *head);
	void setTail(node *tail);
	void moveCursorToNext(void);

	void addNodeToHead(node *newNode);
	void addNodeToTail(node *newNode);
	void delNodeFromHead(void);
	void delNodeFromTail(void);
};



#endif
