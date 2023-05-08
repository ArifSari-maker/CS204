#include <iostream>
using namespace std;

////
/* Arif Kemal Sari*/
///
#ifndef _container
#define _container

struct node{
    int val;
    node* next;
    node(int v=0, node* n=nullptr): val(v), next(n) {}
};

class Container{
public:
	virtual void insertElement(int) = 0;
	virtual void deleteElement(int) = 0;
	virtual void print(void) const = 0;
	virtual ~Container() {}

};



#ifndef DYNINTQUEUE_H
#define DYNINTQUEUE_H

class Queue: public Container{
	private:
		// These track the front and rear of the queue.
		node *front;
		node *rear;	
	public:
		Queue();// Constructor.
	    ~Queue();
		void insertElement(int);
		void deleteElement(int);
		void dequeue(int &);
		bool isEmpty() const;     
		void clear();
		void print(void) const;
};
#endif

#ifndef STACK_H
#define STACK_H

class Stack: public Container{// Dynamically allocated stack
private:
	node *top;

public:
	Stack();
    ~Stack();
	void insertElement(int);
	void deleteElement(int);
	void pop(int &);
	void print(void) const;
	bool isEmpty(void) const;
};
#endif

#ifndef _LINKEDLIST_H
#define _LINKEDLIST_H

class LinkedList: public Container{
public:
    LinkedList();
	~LinkedList();
    void add_Begin(int);
	void insertElement(int);
	void deleteElement(int);
    void print(void) const;
private:
    node* head;
};

#endif

#endif


LinkedList::LinkedList(void){
    head = NULL;
}

LinkedList::~LinkedList(void){
	
	cout<<"Destructing the linked list."<<endl;
	if (head != NULL)
	{   
		node* q;
		node* p = head;
        while (p != NULL){
			q = p;
            p = p->next;
			delete q;
		}
	}
}

/* LinkedList*/

void LinkedList::deleteElement(int num){
	
	
	if((head!=NULL)&&(num == head->val)){
		node* temp_head = head;
		head = head->next;
		delete temp_head;
		cout<<num<<" is deleted from the linked list."<<endl;
	}
	else if(head!=NULL){
		int found = 0;
		node* p = head;
		node* q;
		while ((p != NULL)&&(found==0)){
			q = p->next;
			if((q!=NULL)&&(q->val==num)){
				p->next = q->next;
				delete q;
				found += 1;
			}
            p = p->next;
		}
		if(found!=0){
			cout<<num<<" is deleted from the linked list."<<endl;
		}
		else{
			cout<<num<<" cannot be deleted from the linked list."<<endl;
		}
	}
	else{
		cout<<num<<" cannot be deleted from the linked list."<<endl;
	}

	cout<<endl;
}


void LinkedList::insertElement(int num){ /// insert element ordered
	
	if ((head == NULL)||(num<head->val)){
		add_Begin(num);
	}
	else{
		int n = 0;
		node* p = head;
		node* q;
        while ((p != NULL)&&(n==0)){
			q = p;
			p = p->next;
			if((p != NULL)&&(num<p->val)){
				q->next = new node(num,p);
				n += 1;
			}
           
		}
		if(n==0){
			q->next = new node(num,NULL);
		}
	}
	cout<<num<<" is inserted into the linked list."<<endl<<endl;
}

void LinkedList::add_Begin(int i){
    head = new node(i, head);
}

void LinkedList::print(void) const{
    cout<<"Printing the linked list:"<<endl;
	if (head != NULL){
        node* p = head;
        while (p != NULL){
            cout << p->val << " ";
            p = p->next;
        }
	}
	cout<<endl<<endl;
}

/* Stack*/
//************************************************
// Constructor to generate an empty stack.       *
//************************************************
Stack::Stack(){
	top = NULL; 
}

Stack::~Stack(void){
	
	cout<<"Destructing the stack."<<endl;
	int value;   
    while(!isEmpty())
		pop(value); 
}

//************************************************
// Member function push pushes the argument onto *
// the stack.                                    *
//************************************************
void Stack::insertElement(int num){
	node *newNode;

	// Allocate a new node & store Num
	newNode = new node;
	newNode->val = num;

	// If there are no nodes in the list
	// make newNode the first node
	if (isEmpty()){
		top = newNode;
		newNode->next = NULL;
	}
    else{	// Otherwise, insert NewNode before top
		newNode->next = top;
		top = newNode;
	}
	cout<<num<<" is inserted into the stack."<<endl<<endl;
}

void Stack::deleteElement(int num){
	if(!isEmpty()){
		if(num==top->val){
			pop(num);
		    cout<<num<<" is deleted from the stack."<<endl;
		}
		else{
			cout<<num<<" cannot be deleted from the stack."<<endl;
		}
	}
	else{
		cout<<num<<" cannot be deleted from the stack."<<endl;
	}
	cout<<endl;
}
//****************************************************
// Member function pop pops the value at the top     *
// of the stack off, and copies it into the variable *
// passed as an argument.                            *
//****************************************************
void Stack::pop(int &num){
	node *temp;

	if (!isEmpty()){
		// pop value off top of stack
		num = top->val;
		temp = top->next;
		delete top;
		top = temp;
	}
}

//****************************************************
// Member funciton isEmpty returns true if the stack *
// is empty, or false otherwise.                     *
//****************************************************
bool Stack::isEmpty(void) const{
	bool status;

	if (top == NULL)
		status = true;
	else
		status = false;

	return status;
}

void Stack::print(void) const{
	
	cout<<"Printing the stack:"<<endl;
	if(!isEmpty()){
		node* temp = top;
		while(temp!=NULL){
			cout << temp->val << " ";
            temp = temp->next;
		}
	}
	cout<<endl<<endl;
}

/*Stack*/
Queue::Queue()//// Constructor.
{
	front = NULL;
	rear = NULL;
}
/*****************
Function clear dequeues all the elements  
***///////
Queue::~Queue(void)
{
	cout<<"Destructing the queue."<<endl;
	int value;   
    while(!isEmpty())
		dequeue(value); 
}

//********************************************
// Function enqueue inserts the value in num *
// at the rear of the queue.                 *
//********************************************
void Queue::insertElement(int num)
{       
	if (isEmpty())   //if the queue is empty
	{	//make it the first element
		front = new node(num);
		rear = front;
	}
	else  //if the queue is not empty
	{	//add it after rear
		rear->next = new node(num);
		rear = rear->next;
	}
	cout<<num<<" is inserted into the queue."<<endl<<endl;
}

void Queue::deleteElement(int num){
	if(!isEmpty()){
		if(num==front->val){
			dequeue(num);
		    cout<<num<<" is deleted from the queue."<<endl;
		}
		else{
			cout<<num<<" cannot be deleted from the queue."<<endl;
		}
	}
	else{
		cout<<num<<" cannot be deleted from the queue."<<endl;
	}
	cout<<endl;
}

//**********************************************
// Function dequeue removes the value at the   *
// front of the queue, and copies it into num. *
//**********************************************
void Queue::dequeue(int &value)
{
	node *temp;
	if (isEmpty())
	{
		exit(1);
	}
	else //if the queue is not empty
	{	//return front's value, advance front and delete old front
		value = front->val;
		temp = front;
		front = front->next;
		delete temp;      
	}
}


/*****************
returns true if  queue is empty, and false otherwise.    
***///////
bool Queue::isEmpty() const
{
	if (front == NULL)
		return true;
	else 
		return false;
}

void Queue::print(void)const{
	
	cout<<"Printing the queue:"<<endl;
	if(!isEmpty()){
		node* temp = front;
		while(temp != rear){
			cout<<temp->val<<" ";
			temp = temp->next;
		}
		cout<<temp->val;
	}
	cout<<endl<<endl;
}