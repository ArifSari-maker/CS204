#include <iostream>
#include "container.h"
using namespace std;

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
	cout<<num<<" is inserted into the stack."<<endl;
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
}