#include <iostream>
#include <string>
#include <vector>
using namespace std;

////* Arif Kemal SARI 28999 *///

int input_nuberofrows(){
int number_rows; 
cin>>number_rows;
return number_rows;
}

vector<vector<char>> input_matrix(int num_rows){
vector<vector<char>> mat(num_rows,vector<char>());
for(int i=0;i<num_rows;i++){
 string line_str_matrix;
cin>>line_str_matrix;
int num_column =line_str_matrix.size();
for(int j=0;j<num_column;j++){
	mat[i].push_back(line_str_matrix[j]);
} }
return mat;
}

int calculating_score(int number_of_words,vector<vector<char>> mat);

int main(){

int number_of_rows=input_nuberofrows();
vector<vector<char>> matrix = input_matrix(number_of_rows);
int nuber_of_words;
cin>>nuber_of_words;
int score=calculating_score(nuber_of_words,matrix);//taking word and find them if they exist and then calulate the score and return it 
cout<<score;
return 0;
}


int finding_word(const string word,const vector<vector<char>> mat){
int score=0;
int found_or_not=0;
int lengt_word = word.length();
int rows = mat.size();  int column= mat[0].size();

for(int i=0;i<rows;i++){
for(int j=0;j<column;j++){
	if(mat[i][j]==word[0]){
	if(lengt_word <=(column-j)){//horizontally and diagonally to the right?

		string search_str1=""; // forming a string that corresponding to the word for searching horizontally
		string search_str2=""; // forming a string that corresponding to the word for searching diagonally
		for(int k=0;k<lengt_word;k++){if((i+k)<column){search_str1 +=mat[i][(j+k)];} if(((i+k)<column)&&((i+k)<rows)){ search_str2 += mat[(i+k)][(j+k)];} }
	
/*checking word exist or not*/if(word==search_str1){
		                          if(lengt_word>5){score+=2;/* words longer than 5 characters contribute 2 extra points to the overall score.*/} 
		                               score +=lengt_word; found_or_not+=1;}
        if(word==search_str2){ if(lengt_word>5){score+=2;} score +=(lengt_word*2); found_or_not+=1; }	
}
	if(lengt_word<=(j+1)){//horizontally and diagonally to the left?
		
	    string search_str1="";// forming a string that corresponding to the word for searching horizontally
		string search_str2="";// forming a string that corresponding to the word for searching diagonally
		for(int l=0;l<lengt_word;l++){if((i-l)>=0){search_str1 += mat[i][(j-l)]; search_str2 += mat[(i-l)][(j-l)];} }
		if(word==search_str1){ if(lengt_word>5){score+=2;}
		score +=lengt_word; found_or_not+=1;}
		if(word==search_str2){ if(lengt_word>5){score+=2;} 
		score += (lengt_word*2); found_or_not+=1; }
}
   if(lengt_word <=rows){ //vertically(up and down)

	   string search_stra="";//forming a string that corresponding to the word for searching vertically(up)
       string search_strb="";//forming a string that corresponding to the word for searching vertically(down)
	   for(int s=0;s<lengt_word;s++){if((i-s)>=0){search_stra += mat[(i-s)][j];} if((i+s)<rows){ search_strb += mat[(i+s)][j];} }  
	   if(word==search_stra){if(lengt_word>5){score+=2;}
	   score += lengt_word; found_or_not+=1; } 
	   if(word==search_strb){if(lengt_word>5){score+=2;} 
	   score += lengt_word; found_or_not+=1; }
   }
}
}}
if(found_or_not==0){score = -5; return score ;}
 return score;

}


int calculating_score(int number_of_words,vector<vector<char>> mat){
int score=0;
for(int l=0;l<number_of_words;l++){
 string word;
 cin>>word;//taking words to read and check
 score+= finding_word(word,mat);//finding word and return the score
}
return score;}