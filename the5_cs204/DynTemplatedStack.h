#ifndef _DYNTEMPLATEDSTACK_H
#define _DYNTEMPLATEDSTACK_H

template <class itemType>
struct node {
	itemType info;
	node *next; 

	node ()
	{}

	node (const itemType & s ,node * link)
		: info(s), next (link)
	{ }
	
};


template <class itemType>
class DynTemplatedStack 
{
	private:
		node<itemType> * top;

	public:
		 DynTemplatedStack();
		 DynTemplatedStack (const DynTemplatedStack &);
         ~DynTemplatedStack ();   //destructor
		 void push(itemType n);
		 void pop (itemType &);
		 const DynTemplatedStack & operator = (const DynTemplatedStack & rhs);
		 node<itemType> * createClone () const;
		 bool isEmpty(void) ;
		 
		 
};

#endif 