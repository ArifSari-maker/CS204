#ifndef _LINKEDLIST_H
#define _LINKEDLIST_H

struct node{
    int val;
    node* next;
    node(int v=0, node* n=NULL): val(v), next(n) {}
};


class LinkedList{
public:
    LinkedList(void);
	~LinkedList(void);
    void add_Begin(int);
	void insertElement(int);
	void deleteElement(int);
    void print(void) const;
private:
    node* head;
};



#endif
