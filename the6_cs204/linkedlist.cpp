#include <iostream>
#include "container.h"
using namespace std;



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
	cout<<num<<" is inserted into the linked list."<<endl;
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
}
