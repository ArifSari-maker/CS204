#include "DynTemplatedStack.h"
using namespace std;
//************************************************
// Constructor to generate an empty stack.       *
//************************************************
template <class itemType>
DynTemplatedStack<itemType>::DynTemplatedStack()
{
	top = NULL;

}

//Copy constructor for deep copy
template <class itemType>
DynTemplatedStack<itemType>::DynTemplatedStack (const DynTemplatedStack<itemType> & copy)
{
	top = copy.createClone();
	
}


//destructor function visits all nodes and returns to heap
template <class itemType>
DynTemplatedStack<itemType>::~DynTemplatedStack ()
{
	itemType a;
    while (!(isEmpty())) 
	{   
		pop(a);
	   
	}

#ifdef _DEBUG
	cout<<"Destructor called"<<endl;
#endif

} 

//************************************************
// Member function push pushes the argument onto *
// the stack.                                    *
//************************************************

template <class itemType>
void DynTemplatedStack<itemType>::push (itemType T)
{   
	// Allocate a new node & store info
	node<itemType> *ptr = new node<itemType>;
	ptr->info = T;
    
	// If there are no nodes in the list
	// make newNode the first node
	if (isEmpty()){
		top = ptr;
		ptr->next = NULL;
	}
    else{	// Otherwise, insert NewNode before top
		ptr->next = top;
		top = ptr;
	}
}	

//****************************************************
// Member function pop pops the value at the top     *
// of the stack off, and copies it into the variable *
// passed as an argument.                            *
//****************************************************


template <class itemType>
void DynTemplatedStack<itemType>::pop (itemType & info)
{
	node<itemType> * ptr = top;

	if (isEmpty()){
		cout << "The stack is empty.\n";
	}
    else{
		if(top->next!=NULL){	// pop value off top of stack
			info = top->info;
		    top = top->next;
		    delete ptr;
		}
		else{
			info = top->info;
			top = NULL;
			delete ptr;
		}
	}
}


template <class itemType>
bool DynTemplatedStack<itemType>::isEmpty(void){
	bool Check_status = true;

	if(top == NULL){
		Check_status = true;
	}
	else{
		Check_status =false;
	}
	return Check_status;
}


template <class itemType>
const DynTemplatedStack<itemType> & DynTemplatedStack<itemType>::operator = (const DynTemplatedStack<itemType> & rhs)
{
	if (this != &rhs)
	{
		itemType a;
		while (!(isEmpty())) 
		{
			pop(a);
		}
		top = rhs.createClone();
	}
	return *this;

}


//generates a clone of the stack object by generating new copies of
//each node and connecting them as in the original.
//Returns the top of the clone stack

template <class itemType>
node<itemType> * DynTemplatedStack<itemType>::createClone () const
{   
	
	if (top == NULL){//if stack is empty
	
		return NULL ; }  //clone is empty as well


	
	node<itemType> * topClone = new node<itemType> (top->info, NULL);
	node<itemType> * ptr = top->next;  //second node in orig.
	node<itemType> * ptrClone = topClone; 
    while (ptr != NULL) 
	{
		ptrClone->next = new node<itemType> (ptr->info, NULL);
		ptr = ptr->next;
		ptrClone = ptrClone->next;
	}
	
	return topClone;
} 
