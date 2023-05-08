/*******************
Purpose: Doubly Circular Linked List
Usage: Store items of shopping list in sorted way and update if  necessary commands are given
Author: Arif Kemal SARI - No: 28999
Date: 8/17/2022
*******************/
#include <iostream>
#include <string>

using namespace std;
struct node{
	string name_item;
	int price;
    int count;
    int total_price;
    node * next;
    node * prev;
	
	node (){}
	
	node(string w,int n,int t, node * p, node * q){
		price= n;
		count= t;
        total_price=n*t;
        name_item = w;
        next  = p;
        prev = q ;
	}

};


void add_newNode(node * & ptr,string name,int price,int quantity){	ptr=new node;
    ptr->name_item= name;
	ptr->price=price;
    ptr->count= quantity;
	ptr-> total_price= price*quantity;
}


bool item_in_List_or_Not(node * last,string name,int price,int quantity){  
	
	if(last==NULL){
		return false;}
	
	else {
		if(last->name_item==name){
			if(price<last->price){
				last->price= price;
			}
			last->count += quantity;
			last->total_price = (last->count)*(last->price);
			return true; }
		else{
			if(last->next!=last){
				node * ptr= last->next;
				while(ptr!=last){
					if(ptr->name_item==name){
						if(price<ptr->price){
							ptr->price = price;
						}
						ptr->count += quantity;
						ptr->total_price = (ptr->count)*(ptr->price);
						return true; }
					ptr = ptr->next;
				}
			}
			return false;
		}
	}

}

// find_alphabetical_order Return True if new_name comes before last_name  alphabetically, false otherwise .
bool find_alphabetical_order(string last_name, string new_name){ 
	if(last_name<new_name){ 
		return true; }  

	else { return false;}
}





void add_item(node * & last , node * & first){
	
	string name;
	cin.ignore();
    getline(cin, name);
	int quantity,price;
	cin>>quantity>>price;

	int total_point = quantity*price;

	if(item_in_List_or_Not(last,name,price,quantity)){
	}
	
	else {
		
		if(last==NULL){
			add_newNode(last,name,price,quantity);
		    last->next=last;
		    last->prev=last;
		    first = last; }

		else if(first== last){
			if((last->total_price<total_point)||((last->total_price==total_point)&&find_alphabetical_order(name,last->name_item))){
				add_newNode(first,name,price,quantity);
			}
			else{
				add_newNode(last,name,price,quantity);
				
			}
			last->next = first;
			last->prev = first;
			first->next = last;
			first->prev = last;
		}
		
		
		else {
			// update first node
			if((first->total_price<total_point)||((first->total_price==total_point)&&find_alphabetical_order(name,first->name_item)))
			{
				node * ptr = first;
                add_newNode(last->next,name,price,quantity);
		        first=last->next;
		        ptr->prev= first;
		        first->next= ptr;
		        first->prev=last; 
		        ptr = NULL;
			}
			
			else {
				node * p= first->next;
				while(p!=first) {
					if(total_point>(p->total_price)&&(total_point<(p->prev)->total_price||(((p->prev)->total_price==total_point)&&find_alphabetical_order((p->prev)->name_item,name))))
					{
						node * q = p->prev;
						add_newNode(p->prev,name,price,quantity);
						q->next= p->prev;
				        (q->next)->prev = q;
				        (p->prev)->next =p; 
				        q= NULL;  }
					
					else if(p==last){
						if((total_point<(p->total_price))||((last->total_price==total_point)&&find_alphabetical_order(last->name_item,name))){
							add_newNode(p->next,name,price,quantity);
							last = p->next;
							last->prev = p;
							first->prev = last;
							last->next = first;
						}
					}
					p= p->next;
				
				}

				
				p= NULL;
			}
		}
	}

}


void clear_list(node * & last, node * & first){ 
	if(last==NULL){
	  cout<<"The list is cleared."<<endl;
	}
	
	else{
		
		while(first!=last){
			node * p = first;
			first = first->next;
			delete p;
		}
		last = NULL;
		delete first;
		cout<<"The list is cleared."<<endl;
	}
	
}
	

void print_linked_list(node * last);

void print_total_price(node * last);

void delete_item(node * & last,node * & first){
	string delete_item;
	char z='0'; //to check item found and deleted or not
	cin.ignore();
    getline(cin,delete_item);

	if(last==NULL){}// to avoid error
	
	else if(last->name_item==delete_item){
		if(last==first){
			last=NULL;
			delete first;
			cout<<"The item "<<delete_item<<" is deleted from the list."<<endl;
			z='1';
		}
		else{
			node * p= last;
			last = last->prev;
			last->next= first;
			first->prev=last; 
			delete p;
			cout<<"The item "<<delete_item<<" is deleted from the list."<<endl;
			z='1';
		}
	}
	
	else{
		if(last->next!=last){
			node * q = last->prev;
			while(q!=last){
				
				if((q->name_item)==delete_item){
					node * ptr = q;
					q = q->prev;
					if(ptr==first){
						if(ptr->next==last){
							first = last;
							last->next=last;
							last->prev=last;
							delete ptr;
							cout<<"The item "<<delete_item<<" is deleted from the list."<<endl;
							z='1';
						}
						else{
							first = first->next;
							first->prev = last;
							last->next = first;
							delete ptr;
                            cout<<"The item "<<delete_item<<" is deleted from the list."<<endl;
							z='1';
						}
					}
					else{
						(ptr->prev)->next = ptr->next;
						(ptr->next)->prev = ptr->prev;
						delete ptr;
						cout<<"The item "<<delete_item<<" is deleted from the list."<<endl;
						z='1';
					}
				} 
				else{q = q->prev;}
			}
			q = NULL;
		}
	}
	
	if(z =='0'){
		cout<<"The item "<<delete_item<<" could not be found in the list."<<endl;
	}
}	





int main(){
	string input;
	bool check_exit_command= true;
	node * last= NULL;
	node * first= NULL;

	while(check_exit_command){ // taking commands to proceed necessary actions until exit command given 
		
		string input;
		cin>>input;
		if(input=="exit"){    
			check_exit_command= false; }
		
		else if(input=="add"){
			add_item(last, first); }
		
		else if(input=="print"){
			print_linked_list(last); }
		
		else if(input=="totalPrice"){
			print_total_price(last); }
		
		else if(input=="delete"){
			delete_item(last,first); }
		
		else if(input=="clear"){
			clear_list(last,first); }
		
		else {
			cout<<"Invalid command."<<endl; }
		
	}
	
	
	return 0;
}

void print_linked_list( node * last){
	 if(last==NULL){
		cout<<"The shopping list is empty."<<endl;
	}
	else{
		if(last->next!=last){
			node * ptr = last->next;
			while(ptr!=last){
				cout<<"Item: "<<(ptr->name_item)<<endl<<
					  "Quantity: "<<(ptr->count)<<endl<<
				      "Unit Price: "<<(ptr->price)<<endl;
				ptr = ptr->next;
			}
			cout<<"Item: "<<(ptr->name_item)<<endl<<"Quantity: "<<(ptr->count)<<endl<<"Unit Price: "<<(ptr->price)<<endl;
			ptr = NULL;
		}
		else{
			cout<<"Item: "<<(last->name_item)<<endl<<"Quantity: "<<(last->count)<<endl<<"Unit Price: "<<(last->price)<<endl;
		}

	}
	
}

void print_total_price(node * last){
	int total_price_list=0;
	if(last!=NULL){
		int unique_item = 1;
		total_price_list += last->total_price;
		if(last->next!=last){
			node * ptr = last->next;
			while(ptr!=last){
				total_price_list += ptr->total_price;
				ptr = ptr->next;
				unique_item += 1;
			}
			ptr = NULL;
		}
		cout<<"Total price: "<<total_price_list<<endl<<"Unique items: "<<unique_item<<endl;
	}
	else {
		cout<<"The shopping list is empty."<<endl;
	}
	
		
}