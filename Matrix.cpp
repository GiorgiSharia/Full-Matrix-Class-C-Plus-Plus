#include "Matrix.h";
#include <iostream>;

/*Definition of Matrix
It supports basic functionalities of class
in combination with features of Matrix and operator overloading
to ease the work on class instances
*/
using namespace std;


//empty constructor
Matrix::Matrix() {
	cout << "Creating Matrix Object Using Default Constructor\n\n";

	sizeCols = 0;
	sizeRows = 0;
	matPtr = NULL;
};

//constructor with dimensions as arguments

Matrix::Matrix(const int& rows,const int& cols) {
	cout << "Creating Matrix Object Using Constructor With Parameters\n\n";

	sizeRows = rows;
	sizeCols = cols;

	matPtr = (double**)malloc(sizeRows * sizeof(double*));
	for (int i = 0; i < sizeRows; i++) {
		matPtr[i] = (double*)malloc(sizeCols * sizeof(double));
	}
}

//copy constructor
Matrix::Matrix(const Matrix& fromMatr) {
	if (fromMatr.matPtr == NULL) {
		matPtr == NULL;
		sizeCols = 0;
		sizeRows = 0;
		return;
	}
	cout << "Creating Matrix Object Using Copy Constructor\n\n";
	sizeRows = fromMatr.sizeRows;
	sizeCols = fromMatr.sizeCols;

	matPtr = (double**)malloc(sizeRows * sizeof(double*));
	for (int i = 0; i < sizeRows; i++) {
		matPtr[i] = (double*)malloc(sizeCols * sizeof(double));
		for (int j = 0; j < sizeCols; j++) {
			matPtr[i][j] = fromMatr.matPtr[i][j];
		}
	}
}


//destructor
Matrix::~Matrix() {
	if (matPtr == NULL) {
		return;
	}
	if (sizeCols != 0 ) {
		for (int i = 0; i < sizeRows; i++) {
			free(matPtr[i]);
		}
	}
	free(matPtr);
	matPtr = NULL;
}

//public void to get number of rows
int Matrix::getSizeRows() {
	return sizeRows;
}

//public void to get number of cols
int Matrix::getSizeCols() {
	return sizeCols;
}

//for printing matrix
void Matrix::print() {
	if (matPtr == NULL || sizeRows == 0 || sizeCols == 0) {
		throw exception("Error, Matrix uninitialized or contains no values");
	}
	else {
		cout << "\n\nPrinting matrix\n\n";
		for (int i = 0; i < sizeRows; i++) {
			for (int j = 0; j < sizeCols; j++) {
				printf("On position [%d][%d] in array is %lf\n", i, j, matPtr[i][j]);
			}
		}
	}
}

//get value of precise element in matrix
double Matrix::getElement(const int& i,const int& j) {
	if (matPtr == NULL || sizeRows == 0 || sizeCols == 0) {
		throw exception("Error, trying to get value of uninitialized matrix\n");
	}
	else if(i < 0 || i >= sizeRows || j < 0 || j >= sizeCols){
		throw exception("Error index out of bounds\n");	
	}
	else {
		return matPtr[i][j];
	}
}

//set value of precise element in matrix
void Matrix::setElement(const int& i,const int& j,const double& value) {
	if (matPtr == NULL || sizeRows == 0 || sizeCols == 0) {
		throw exception("Error, trying to get value of uninitialized matrix\n");
	}
	else if (i < 0 || i >= sizeRows || j < 0 || j >= sizeCols) {
		throw exception("Error index out of bounds\n");
	}
	else {
		matPtr[i][j] = value;
	}
}

//private void to set number of rows
 void Matrix::setSizeRows(int length) {
	 if (sizeRows != 0) {
		 cout << "size of rows in already set, altering it may result in loss of data. Aborted!\n";
		 throw exception("Error while setting size of rows\n");
	 }
	 else {
		 sizeRows = length;
		 matPtr = (double**)malloc(sizeRows * sizeof(double*));
	 }
	
}
 
 //private void to set number of cols

 void Matrix::setSizeCols(int length) {
	 if (sizeCols != 0) {
		 cout << "size of cols in already set, altering it may result in loss of data. Aborted!\n";
		 throw exception ("Error while setting size of columns\n");
	 }
	 else if (sizeRows == 0) {
		 cout << "size of rows is 0, changing to one\n";
		 sizeRows = 1;
		 sizeCols = length;
		 matPtr = (double**)malloc(sizeRows * sizeof(double*));
		 for (int i = 0; i < sizeRows; i++) {
			 matPtr[i] = (double*)malloc(sizeCols * sizeof(double));
		 }
	 }
	 else {
		 sizeCols = length;
		 matPtr = (double**)malloc(sizeRows * sizeof(double*));
		 for (int i = 0; i < sizeRows; i++) {
			 matPtr[i] = (double*)malloc(sizeCols * sizeof(double));
		 }
	 }
 }

//addittion overloading
 Matrix operator+(const Matrix& mtrx1,const Matrix& mtrx2) {
	 int mtrx1ColSize = mtrx1.sizeCols;
	 int mtrx1RowSize = mtrx1.sizeRows;
	 if ((mtrx1ColSize != mtrx2.sizeCols) || mtrx1RowSize != mtrx2.sizeRows) {
		 throw exception("Error, Matrix sizes should match to perform addition\n");
	 }
	 else {
		 Matrix toReturn(mtrx1RowSize,mtrx1ColSize);
		 for (int i = 0; i < mtrx1RowSize; i++) {
			 for (int j = 0; j < mtrx1ColSize; j++) {
				 toReturn.matPtr[i][j] = mtrx1.matPtr[i][j] + mtrx2.matPtr[i][j];
			 }
		 }
		 return toReturn;
	 }
 }

 //substraction overloading
 Matrix operator-(const Matrix& mtrx1, const Matrix& mtrx2) {
	 int mtrx1ColSize = mtrx1.sizeCols;
	 int mtrx1RowSize = mtrx1.sizeRows;
	 if ((mtrx1ColSize != mtrx2.sizeCols) || mtrx1RowSize != mtrx2.sizeRows) {
		 throw exception("Error, Matrix sizes should match to perform substraction\n");
	 }
	 else {
		 Matrix toReturn(mtrx1RowSize, mtrx1ColSize);
		 for (int i = 0; i < mtrx1RowSize; i++) {
			 for (int j = 0; j < mtrx1ColSize; j++) {
				 toReturn.matPtr[i][j] = mtrx1.matPtr[i][j] - mtrx2.matPtr[i][j];
			 }
		 }
		 return toReturn;
	 }
 }

 //overloading assignment operator 
Matrix& Matrix::operator=(const Matrix& mtrx) {
	 cout << "assignment overload called\n\n";
	 if (matPtr != NULL && sizeCols !=0) {
		 for (int i = 0; i < sizeRows; i++) {
			 free(matPtr[i]);
		}
		 free(matPtr);
	 }
	 if (mtrx.matPtr == NULL) {
		 matPtr == NULL;
		 sizeCols = 0;
		 sizeRows = 0; 
	 } else {
		 sizeRows = mtrx.sizeRows;
		 sizeCols = mtrx.sizeCols;
		 matPtr = (double**)malloc(sizeRows * sizeof(double*));
		 for (int i = 0; i < sizeRows; i++) {
			 matPtr[i] = (double*)malloc(sizeCols * sizeof(double));
			 for (int j = 0; j < sizeCols; j++) {
				 matPtr[i][j] = mtrx.matPtr[i][j];
			 }
		 }
		 return *this;
	 }
 }

//overload of compound assisgnment/addition
Matrix& Matrix::operator+=(const Matrix& mtrx) {
	if ((sizeRows != mtrx.sizeRows) || (sizeCols != mtrx.sizeCols)) {
		throw exception("Error, Matrix sizes should match to perform addition/assignment\n");
	}
	else {
		for (int i = 0; i < sizeRows; i++) {
			for (int j = 0; j < sizeCols; j++) {
				matPtr[i][j] += mtrx.matPtr[i][j];
			}
		}
		return *this;
	}
}

//overload compound assignment/substraction -=
Matrix& Matrix::operator-=(const Matrix& mtrx) {
	if ((sizeRows != mtrx.sizeRows) || (sizeCols != mtrx.sizeCols)) {
		throw exception("Error, Matrix sizes should match to perform substraction/assignment\n");
	}
	else {
		for (int i = 0; i < sizeRows; i++) {
			for (int j = 0; j < sizeCols; j++) {
				matPtr[i][j] -= mtrx.matPtr[i][j];
			}
		}
		return*this;
	}
}

//overload compound operator of assignment and multiplication
Matrix& Matrix::operator*=(const Matrix& mtrx1) {
	if (sizeCols == 0 || mtrx1.sizeCols == 0 || mtrx1.matPtr == NULL || matPtr == NULL) {
		throw exception("Error,while trying to multiply\n");
	}
	else if (sizeRows != mtrx1.sizeCols) {
		throw exception("Matrixes can not be multiplied, number of columns in first does not match number of rows in second\n\n");

	}
	else {
		double counter = 0.0;
		Matrix toReturn = Matrix(mtrx1.sizeRows, sizeCols);
		for (int i = 0; i < sizeCols; i++) {
			for (int j = 0; j < mtrx1.sizeRows; j++) {
				for (int k = 0; k < sizeRows; k++) {
					counter += matPtr[k][i] * mtrx1.matPtr[j][k];
				}

				toReturn.matPtr[j][i] = counter;
				counter = 0.0;
			}
		}
		*this = toReturn;
		return *this;
	}
}

//overload comparison function ==
 bool operator==(const Matrix& mtrx1,const  Matrix& mtrx2) {
	 if ((mtrx1.sizeRows != mtrx2.sizeRows) || (mtrx1.sizeCols != mtrx2.sizeCols)) {
		 return false;
	 }
	 for (int i = 0; i < mtrx1.sizeRows; i++) {
		 for (int j = 0; j < mtrx1.sizeCols; j++) {
			 if (mtrx1.matPtr[i][j] != mtrx2.matPtr[i][j])return false;
		 }
	 }
	 return true;
 }
 
//overload scalar multiplication 
void Matrix::operator^(const double& a) {
	if (matPtr == NULL || sizeCols == 0) {
		throw exception("Error, Matrix is not initialized\n");
		return;
	}
	else {
		for (int i = 0; i < sizeRows; i++) {
			for (int j = 0; j < sizeCols; j++) {
				matPtr[i][j] *= a;
			}
		}
	}
}

//overload transposing using ! as operator
Matrix Matrix::operator!() {
	if (matPtr == NULL || sizeCols == 0) {
		throw exception("Error, Matrix is not initialized, what are you transposing ??\n");
	}
	else {
		Matrix temp = Matrix(sizeCols, sizeRows);
		for (int i = 0; i < sizeRows; i++) {
			for (int j = 0; j < sizeCols; j++) {
				temp.setElement(j, i, matPtr[i][j]);
			}
		}
		return temp;
	}
}

//overload multiplication operator
Matrix operator*(const Matrix& mtrx1,const Matrix& mtrx2) {
	if (mtrx1.sizeCols == 0 || mtrx2.sizeCols == 0 || mtrx1.matPtr == NULL || mtrx2.matPtr == NULL) {
		throw exception("Error,while trying to multiply\n");
	}
	else if(mtrx1.sizeRows != mtrx2.sizeCols) {
		throw exception("Matrixes can not be multiplied, number of columns in first does not match number of rows in second\n\n");
	}
	else {
		double counter = 0.0;
		Matrix toReturn = Matrix(mtrx2.sizeRows, mtrx1.sizeCols);
		for (int i = 0; i < mtrx1.sizeCols; i++) {
			for (int j = 0; j < mtrx2.sizeRows; j++) {
				for (int k = 0; k < mtrx1.sizeRows; k++) {
					counter += mtrx1.matPtr[k][i] * mtrx2.matPtr[j][k];
				}
				
				toReturn.matPtr[j][i] = counter;
				counter = 0.0;
			}
		}
		toReturn.print();
		return toReturn;
	}
}

//overload for ostream operator <<
ostream& operator<<(ostream& os,const Matrix& mtrx1) {
	for (int i = 0; i < mtrx1.sizeRows; i++) {
		for (int j = 0; j < mtrx1.sizeCols; j++) {
			os << mtrx1.matPtr[i][j] << " is the value on position " << i << " , "<<j <<"\n";
		}
	}
	return os;
}
//overload for istream operator >>
istream& operator>>(istream& is, Matrix& mtrx1) {
	if (mtrx1.sizeCols == 0 && mtrx1.sizeRows == 0) {
		int sizeCol = 0;
		int sizeRow = 0;
		cout << "\nEnter size of rows as integer:\n";
		is >> sizeRow;
		cout << "\nEnter size of columns as integer:\n";
		is >> sizeCol;
		mtrx1.setSizeRows(sizeRow);
		mtrx1.setSizeCols(sizeCol);
	}
	
	for (int i = 0; i < mtrx1.sizeRows; i++)
		for (int j = 0; j < mtrx1.sizeCols; j++) {
			printf("\nEnter double value for position[%d][%d]\n", i, j);
			is >> mtrx1.matPtr[i][j];
		}
	
	return is;
}