#ifndef Matrix_H
#define Matrix_H
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <math.h>

class matrix
{
	public:
		void getdata();
		void identity(int);
		void null();
		void show();
		float det(int);
		int getrow();
		int getcol();
		matrix(int ,int);
		matrix operator+(matrix);
		matrix operator-(matrix);
		matrix operator*(matrix);
		matrix transpose();
		matrix inv();
		matrix con_to_mtrx(float **a , int row , int col);
		
		float mat[50][50];
		

	private:
		int row;
		int col;
		
};
#endif
