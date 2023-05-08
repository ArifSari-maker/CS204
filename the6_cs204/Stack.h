#ifndef DYNSTACK_H
#define DYNSTACK_H


struct node{
    int val;
    node* next;
    node(int v=0, node* n=nullptr): val(v), next(n) {}
};

class DynIntStack{
private:
	node *top;

public:
	DynIntStack(void);
	~DynIntStack(void);
	void insertElement(int);
	void deleteElement(int);
	void pop(int &);
	void print(void) const;
	bool isEmpty(void) const;
};

#endif