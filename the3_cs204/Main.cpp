/**************** 
Arif Kemal Sar� 28999 
*********************/

#include <iostream>
#include <fstream>
#include "DynTemplatedStack.h"
#include <string>
#include "DynTemplatedStack.cpp"


using namespace std;

template <class type_name> 
bool exist_in_stack( type_name search_item, DynTemplatedStack<type_name> & main_stack){
	bool exist_or_not = false;
	
	DynTemplatedStack<type_name> temp_stack = main_stack;
	type_name a;
	while(!(temp_stack.isEmpty())){
		temp_stack.pop(a);
		
		if (search_item==a){
			exist_or_not = true;/// look at copy const - add return exist_or_not
			#ifdef _DEBUG
            cout<<"function exist called-found"<<endl;
            #endif
			return exist_or_not;
		}
	}
	
#ifdef _DEBUG
cout<<"function exist called"<<endl;
#endif
	return exist_or_not;

} 

template <class type_name>
DynTemplatedStack<type_name> reverse_order_stack(DynTemplatedStack<type_name> & base){

	DynTemplatedStack<type_name> temp_stack;
	DynTemplatedStack<type_name> return_stack;
	type_name c;
	while(!base.isEmpty()){
		base.pop(c);
		temp_stack.push(c);
		return_stack.push(c);
	}
	while(!temp_stack.isEmpty()){
		temp_stack.pop(c);
		base.push(c);
	}
    return return_stack;
}

template <class type_name>
DynTemplatedStack<type_name> read_second(string name_file){
	ifstream file2;
	file2.open(name_file, ios::in);
	if (!(file2.is_open())) {
		DynTemplatedStack<type_name> empty;
		return  empty;
	}
	else{
		DynTemplatedStack<type_name> second;
			    type_name token;
				while (file2 >> token ) {
					second.push(token);
				}
				file2.close();
				second = reverse_order_stack(second);
				return second;
	}

}

template <class type_name>
int count_item (const type_name & search_item,const DynTemplatedStack<type_name> & stack ){
	
	int count_occurence = 0;
	DynTemplatedStack<type_name> copy_find = stack;
	type_name item;
	while(!(copy_find.isEmpty())){
		
		copy_find.pop(item);
		if (search_item == item ){
			count_occurence += 1;
		}
	}

	return count_occurence;
}

template <class type_name>
void display_common_items( DynTemplatedStack<type_name> & first, DynTemplatedStack<type_name> & second){

	type_name search_item;
	int first_stack; 
	int second_stack;
	DynTemplatedStack<type_name> common_items;
	DynTemplatedStack<int> items_numbers;
	DynTemplatedStack<type_name> first_copy = first;
	

	while(!(first_copy.isEmpty())){
		first_copy.pop(search_item);
		
		if(exist_in_stack(search_item,second)){
			
			if(!(exist_in_stack(search_item,common_items))){
				common_items.push(search_item); 
				first_stack = count_item(search_item,first);
				second_stack = count_item(search_item,second);
				
				if(first_stack < second_stack ){
					items_numbers.push(first_stack);
				}
				else{
					items_numbers.push(second_stack);
				}
			}
		}
	}
	common_items = reverse_order_stack(common_items);
	items_numbers = reverse_order_stack(items_numbers);
	
	cout<<"TOKEN --> MINIMUM OCCURRENCE COUNT"<<endl
		<<"----------";
	while(!(common_items.isEmpty())&&!(items_numbers.isEmpty())){
		
		common_items.pop(search_item);
		items_numbers.pop(first_stack);

		cout<<endl<<search_item<<" "<<"-->"<<" "<<first_stack;
	}
	cout<<endl;
	
}




int main(){

	string first_file, second_file;
	char num_of_order;///

	cin>>first_file>>second_file;
    cin>>num_of_order;

	ifstream file;
	file.open(first_file, ios::in);

	if (!(file.is_open())) {
		cout << "File not found.";
	}
	else{ 
		if(first_file.size()>1){

			if(first_file[0]=='s'){
			    DynTemplatedStack<string> first;
			    string token;
				while (file >> token ) {
					first.push(token);
				}
				first = reverse_order_stack(first);
				file.close();
				DynTemplatedStack<string> second = read_second<string>(second_file); 
                if(!second.isEmpty()){
					if(num_of_order=='1'){
						display_common_items(first,second);}
					else if(num_of_order=='2'){
						display_common_items(second,first);}
					else{
						cout<<"Invalid choice."<<endl;}
				}
				else{
					cout<<"File not found"<<endl;
				}
			}
			else if(first_file[0]=='i'){
				DynTemplatedStack<int> first;
			    int token;
				while (file >> token ) {
					first.push(token);
				}
				first = reverse_order_stack(first);
				file.close();
				DynTemplatedStack<int> second = read_second<int>(second_file);
                if(!second.isEmpty()){
					if(num_of_order=='1'){
						display_common_items(first,second);}
					else if(num_of_order=='2'){
						display_common_items(second,first);}
					else{
						cout<<"Invalid choice."<<endl;}
				}
				else{
					cout<<"File not found"<<endl;
				}
			}
			else{
				DynTemplatedStack<char> first;
			    char token;
				while (file >> token ) {
					first.push(token);
				}
				first = reverse_order_stack(first);
				file.close();
				DynTemplatedStack<char> second = read_second<char>(second_file);
				if(!second.isEmpty()){
					if(num_of_order=='1'){
						display_common_items(first,second);}
					else if(num_of_order=='2'){
						display_common_items(second,first);}
					else{
						cout<<"Invalid choice."<<endl;}
				}
				else{
					cout<<"File not found"<<endl;
				}
			}
			
			
		}
		else{
			cout<<"File not found"<<endl;
			file.close(); }
	
}
	
	
	return 0;
}

