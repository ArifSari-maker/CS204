#ifndef _myupdatedmatrixclass
#define _myupdatedmatrixclass
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;

class Matrix2D {
    
    private: 
		int rows, cols;
		int **data;
    public:

		friend ifstream & operator>>(ifstream &, Matrix2D&);
        friend ostream & operator<<(ostream &, const Matrix2D&);

		Matrix2D(); //default constructor
		Matrix2D(const int &, const int &); // constructor with parameters
		Matrix2D (const Matrix2D &);  //copy constructor
	    ~Matrix2D ();
		int GetIndex(const int &, const int &) const;
		void SetIndex(const int &, const int &, const int &) const;
		void clear();
		const Matrix2D & operator=(const Matrix2D&);
		const Matrix2D & operator+=(const Matrix2D&);
	    Matrix2D  operator+(const Matrix2D&) const;
		int get_row_num()const;
		int get_col_num()const;
		bool isEmpty(void)const;
};

Matrix2D::Matrix2D(){
	data = NULL;
	rows = 0;
	cols = 0;
}

Matrix2D::Matrix2D(const int & r, const int & c): rows(r), cols(c) {
	data = new int* [r]; 
	for (int i = 0; i<rows; i++) 
		data[i] = new int[cols];

}

void Matrix2D::clear(){
	if(!(isEmpty())){
		for(int i=0;i<rows;++i){
			delete [] data[i];
		}
		delete [] data;
		cols=0;
		rows= cols;
		data = NULL;
	}
}

//destructor function visits all arrays and returns to heap
Matrix2D::~Matrix2D(){
	
	clear();

	#ifdef _DEBUG
	cout<<"Destructor called"<<endl;
    #endif
}

Matrix2D::Matrix2D (const Matrix2D & copy){
	data = NULL;
	*this = copy;
}

int Matrix2D::GetIndex(const int & i, const int & j) const{
    return data[i][j];
}

void Matrix2D::SetIndex(const int & i, const int & j, const int &value) const {
    
	data[i][j] = value;

}

int Matrix2D::get_row_num() const {
	return rows;
}

int Matrix2D::get_col_num() const {
	return cols;
}

bool Matrix2D:: isEmpty() const {
	if(data==NULL){
		return true;
	}
	else{
		return false;
	}

}

const  Matrix2D & Matrix2D:: operator =(const Matrix2D& rhs){
	clear();
	if(rhs.data==NULL){
		
		return *this;
	}
	rows = rhs.rows;
	cols = rhs.cols;
	data = new int* [rows];
	for (int i = 0; i<rows; i++) 
		data[i] = new int[cols];


    for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			data[i][j] = rhs.data[i][j];
		}
	}
	return *this;	
}


ifstream & operator >>(ifstream & ifs, Matrix2D& rhs){
	 
	int rows_num = 0;  //= memory leak thinks
	int col_num = 0;
	string lin;
	while(getline(ifs,lin)){
		rows_num += 1;
		if(col_num==0){
			istringstream iss(lin);
		    int num0;
		    while(iss>>num0){
				col_num += 1;
			}
		}
	}
    ifs.clear();
	ifs.seekg(0);
    Matrix2D m(rows_num,col_num); 
	rhs = m;
	string line;
	int row = 0;
    while(getline(ifs,line)){
		
		int col = 0;
		istringstream iss(line);
		int num;

		while(iss >> num){
		   rhs.SetIndex(row,col,num);
		   col += 1;
		}
	    row += 1;
	}
	
	return ifs;

}

ostream & operator<<(ostream &os,const Matrix2D& mat)
{ 
	if(!mat.isEmpty()){
	int row= mat.get_row_num();
    int col = mat.get_col_num();

	for (int i = 0; i <row; i++)
	{
		for (int j = 0; j <col; j++)
		{
			os<<setw(6)<<mat.GetIndex(i,j);
		}
		os<<endl;
	}
	}
	return os;
}

const Matrix2D & Matrix2D::operator+=(const Matrix2D& rhs){
	
	if((rows!=rhs.rows)||(cols!=rhs.cols)){
		cout<<"Size not equal. Operator+= is a no-op!"<<endl;
		return *this;
	}
	else{
	Matrix2D temp_matrix(*this);
    clear();
	*this = temp_matrix + rhs;
	temp_matrix.clear();
	
	return *this;
	}
}


 Matrix2D Matrix2D::operator+(const Matrix2D& rhs) const{
	
	Matrix2D new_matrix;
	if((rows!=rhs.rows)||(cols!=rhs.cols)){
		cout<<"Size not equal. Operator+ is a no-op!"<<endl; 
		return new_matrix;
	}
	else{
	new_matrix = rhs;
	for (int i = 0; i < rhs.rows; i++)
	{
		for (int j = 0; j < rhs.cols; j++)
		{
			new_matrix.data[i][j] = rhs.data[i][j]+ data[i][j];
		}
	}
	
	return new_matrix; 
	}
}



#endif
