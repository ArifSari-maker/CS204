#ifndef DYNINTQUEUE_H
#define DYNINTQUEUE_H

using namespace std;

struct node{
    int val;
    node* next;
    node(int v=0, node* n=NULL): val(v), next(n) {}
};

class Queue{
	private:
		// These track the front and rear of the queue.
		node *front;
		node *rear;	
	public:
		Queue();// Constructor.
		~Queue(void);
		void insertElement(int);
		void deleteElement(int);
		void dequeue(int &);
		bool isEmpty() const;     
		void clear();
		void print(void) const;
};
#endif