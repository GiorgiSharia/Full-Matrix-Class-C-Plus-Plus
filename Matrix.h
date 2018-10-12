#pragma once
#include<iostream>
using namespace std;

//declaration of matrix class
class Matrix {

	public:
		Matrix();
		Matrix(const int& sizeRows,const int& sizeCols);
		Matrix(const Matrix&);
		~Matrix();
		int getSizeRows();
		int getSizeCols();
		double getElement(const int& row,const int& column);
		void setElement(const int& row, const int& column,const double& value);
		void setSizeRows(int length);
		void setSizeCols(int length);
		void print();
		Matrix& operator=(const Matrix& mtrx);
		Matrix& operator+=(const Matrix& mtrx1);
		Matrix& operator-=(const Matrix& mtrx1);
		Matrix& operator*=(const Matrix& mtrx1);
		void operator^(double a);
		Matrix operator!();
		friend bool operator==(Matrix& mtrx1, Matrix& mtrx2);
		friend Matrix operator+(Matrix& mtrx1,Matrix& mtrx2);
		friend Matrix operator-(Matrix& mtrx1, Matrix& mtrx2);
		friend Matrix operator*(Matrix& mtrx1, Matrix& mtrx2);
		friend ostream& operator<<(ostream& os, Matrix& mtrx1);
		friend istream& operator>>(istream& is, Matrix& mtrx1);
	private:
		double ** matPtr;
		int sizeRows;
		int sizeCols;	
};



