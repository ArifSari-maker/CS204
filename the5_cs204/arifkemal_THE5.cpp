#include <iostream>
#include <mutex>
#include <string>
#include <fstream>
#include <thread>
#include <sstream>
#include <vector>
#include <stack>
#include "Queue.h" 
#include "randgen.h"
#include <chrono>

/*********
Arif Kemal Sari-28999
************///
using namespace std;

int find_key(const vector<char> & ); // taking vector of characters from consumer and return shifting value (key)
char find_most_occurred_char(const vector<char> &,const vector<int> &); // find most occured charter in file 
bool exist_in_stack( char, vector<char> &);// check given char exist in given stack return true if exist otherwise false
int count_item (const char &,const vector<char> &); // determine occurrence of a given char in given vector and return number of occurence. if not exist return zero.
string decryption(string, int); //decrypt given string with help of given key(number for shifting operation). return decrypted word(string).
int stack_end = 0;
mutex mutex1,mutex2,mutex3,mutex4,mutex5,mymutex1;

// take file names from stack and queue to main queue in order to read by consumer function
void producer(const int i,stack<string> & stack, Queue & main_que){ 
	
	
	RandGen r;
	while(!stack.empty()){
	int d= r.RandInt(1000,4000);
	mutex1.lock();
	cout<<"Producer Thread - "<<i<<" starts sleeping for "<<d<<" milliseconds"<<endl;
	this_thread::sleep_for (chrono::milliseconds(d));
	mutex1.unlock();
	
	mutex2.lock();

	if(!stack.empty()){
	string file_name = stack.top();
	cout<<"Producer Thread - "<<i<<" is now enqueuing "<<file_name<<endl;
    main_que.enqueue(file_name);
	stack.pop();
	}
	mutex2.unlock();
	}
	mutex4.lock();
	cout<<"Producer Thread - "<<i<<" cannot find any file to enqueue, joining..."<<endl;
	mutex4.unlock();
	stack_end += 1;
	
}

 //consumer function is dequeue main queue end decrypted it  and write its content on new file
void consumer(const int i,Queue & main_que){// new created file names end with _decrypted

	RandGen r;
	int d= r.RandInt(2500,3500);
	mutex1.lock();
	cout<<"Consumer Thread - "<<i<<" starts sleeping for "<<d<<" milliseconds"<<endl;
	this_thread::sleep_for (chrono::milliseconds(d));
	mutex1.unlock();
	
	while((stack_end == 0)||(!main_que.isEmpty())){
		
		mutex3.lock();
	    string file_name;
	    int file_defined = 0;
	    if(!main_que.isEmpty()){
			main_que.dequeue(file_name);
			cout<<"Consumer Thread - "<<i<<" is now handling "<<file_name<<endl;
			file_defined += 1;
		}
		mutex3.unlock();
		
		
		mymutex1.lock();
		if(file_defined !=0){
			ifstream file;
	        file.open(file_name,ios::in);  
	        if(!(file.is_open())){
				cout<<"Consumer Thread - "<<i<<" cannot process "<<file_name<<", there is no such file!"<<endl;
			}
			
			else{
				vector<char> char_list;
			    char a;
			    while(file>>a){
					char_list.push_back(a);   //read file to find the most occurring character
				}
			    file.clear();
	            file.seekg(0);
			    int key_num = find_key(char_list); // find key(shifting number) to decrypt file
			    string line,new_file_name = file_name ;
				
				if(new_file_name.length()>=4){
					string txt = new_file_name.substr(new_file_name.length()-4);    //if file_name end with .txt , create substring to avoid name.txt_descrypted.txt
					if(txt==".txt"){
						new_file_name = file_name.substr(0,file_name.length()-4);
					}
				}
				new_file_name += "_decrypted.txt"; 
			
			    fstream new_file;
		        new_file.open(new_file_name, ios::out);
				if (!new_file) {
					cout << "File not created!";
				}
				else{
					bool check_encrypted_ornot = true; /// if key is zero, no shifting therefore decryption is unnecessary.Boolean to check encrypted or not. 
		            if(key_num==0){
						check_encrypted_ornot = false;
#ifndef _DEBUG
						cout<<file_name<<" No encryption."<<endl;
#endif
					}
					
					cout<<"Consumer Thread - "<<i<<" is done handling "<<file_name<<" with a shift of "<<key_num<< " and written the result to "<<endl<<new_file_name<<endl;
					while(getline(file,line)){  /// read and decrypt file and write to new file
						string word;
					    istringstream ss(line);
					    while(ss>>word){
							string decrypted_word = word;
						    if(check_encrypted_ornot){
								decrypted_word = decryption(word,key_num);
							}
							new_file<<decrypted_word<<" ";
						}
						new_file<<endl;
					}
				}
			}
		}
		mymutex1.unlock();

		d= r.RandInt(2500,3500);
	    cout<<"Consumer Thread - "<<i<<" starts sleeping for "<<d<<" milliseconds"<<endl;
	    this_thread::sleep_for (chrono::milliseconds(d));
	
	}
	
	mutex5.lock();
	cout<<"Consumer Thread - "<<i<<" cannot find any file to dequeue, joining..."<<endl;
	mutex5.unlock();
}



int find_key(const vector<char> & char_list){
	
	vector<char> new_char_list;
	vector<int> count_stack;
	int count_num;
    char item;

	for(unsigned int i = 0;i<char_list.size();i++){
	    item = char_list[i];

		if(!exist_in_stack(item,new_char_list)){
			new_char_list.push_back(item);
			count_num = count_item(item,char_list);
		    count_stack.push_back(count_num);
		}
	}
	
	char key_char = find_most_occurred_char(new_char_list,count_stack);//// most occurred char in a text which should be 'e' in English

	int key = key_char - 'e'; /// the text to be used contains all lowercase letters
	
	return key;
}


bool exist_in_stack( char search_item, vector<char> & char_list){
	
	bool exist_or_not = false;

	for(unsigned int i=0;i<char_list.size();i++){
		if(search_item==char_list[i]){
			exist_or_not = true;
			return exist_or_not;
		}
	}
	return exist_or_not;

} 


int count_item (const char & search_item,const vector<char> & char_list ){
	
	int count_occurence = 0;
	char item;
	for(unsigned int i = 0;i<char_list.size();i++){
		item = char_list[i];
		if (search_item == item ){
			count_occurence += 1;
		}
	}
	return count_occurence;
}


char find_most_occurred_char(const vector<char> & char_list,const vector<int> & occurrence_list){
	
	int key_num = 0; 
	char key;
	for(unsigned int i=0;i<char_list.size();i++){
		
		if(occurrence_list[i]>key_num){
			key_num = occurrence_list[i];
			key = char_list[i];
		}
	}
	return key;
}




int main(){

	string input_que;
	stack<string> input_stack;
	cout<<"Please enter a file name: ";
	cin>> input_que;
	
	while(input_que!="-"){
		input_stack.push(input_que);
		cout<<"Please enter a file name: ";
		cin>>input_que;
	}

	Queue main_queu;

	thread t1_prod(&producer,1,ref(input_stack),ref(main_queu));
	thread t2_prod(&producer,2,ref(input_stack),ref(main_queu));

	
    thread t1_cons(&consumer,1,ref(main_queu));
    thread t2_cons(&consumer,2,ref(main_queu));
    thread t3_cons(&consumer,3,ref(main_queu));


	t1_prod.join();
	t2_prod.join();
	t1_cons.join();
	t2_cons.join();
	t3_cons.join();
	


	cout<<"All threads have joined with main, exiting..."<<endl;

	return 0;


}

//decrypt given string with help of given key(number for shifting operation)/// only working for lowercase letter
string decryption(string word, int key){ ///taking encrypted string and number for shifting as parameter- return decrypted word(string)
	
	string new_word = "";
	bool check_negative_key = false;
	if(key<0){
		check_negative_key = true;
	}
	for(unsigned int i=0;i<word.length();i++){
		
		char ch = word[i];
		if(ch >= 'a' && ch <= 'z'){ /// To check lowercase letter to avoid decryption of numbers and punctuation
			ch = ch - key;
			if(check_negative_key){/// to check negative shifting 
				if (ch > 'z') {
					ch = ch - 'z' + 'a' - 1;
				}
			}
			else if (ch < 'a'){ ///check after shifting characters can go outside the lowercase letters char range which results wrong description
				ch = ch +'z' - 'a' + 1;
			}
		}
		
		new_word += ch;
	
	}
	
	return new_word;
}
