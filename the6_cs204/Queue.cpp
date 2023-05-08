#include <iostream>
#include "container.h"
using namespace std;

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
	cout<<num<<" is inserted into the queue."<<endl;
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
}

