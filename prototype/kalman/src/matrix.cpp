#include "matrix.h"

matrix::matrix(int r , int c)
{
	//std::cout << "matrix object created\n";
	row = r;
	col = c;
}

int matrix::getrow()
{
	return row;
}

int matrix::getcol()
{
	return col;
}

void matrix::getdata()
{	std::cout << "enter data in row wise fashion:\n";
	for(int i = 0; i<row ; i++)
	{
		for(int j = 0 ; j < col ; j++)
		{
			std::cin >> mat[i][j];
		}
	}
}

void matrix::identity(int size)
{
	if(row != size || col != size)
	{
		std::cout << "cant initialize to identity matrix\n";
	}
	else
	{
		std::cout << "creating identity matrix\n";
		for(int i = 0 ; i<size ; i++)
		{
			mat[i][i] = 1.0;
		}
	}
}
void matrix::null()
{
	for(int i = 0 ; i<row ; i++)
		{
			for(int j = 0; j < col ; j++)
			{
				mat[i][j] = 0.0;
			}
		}
}

void matrix::show()
{
	for(int i = 0; i<row ; i++)
	{
		for(int j = 0 ; j < col ; j++)
		{
			printf("%9.6f ", mat[i][j]);
		}
		std::cout << "\n";
	}
}

matrix matrix::operator+(matrix m)
{
	matrix a(row,col);
	if(m.getrow()!=row || m.getcol()!=col)
	{
		std::cout << "invalid  + operation\n";
	}
	else
	{
		for(int i = 0 ; i < row ; i++)
		{
			for(int j=0 ; j<col ; j++)
			{
				a.mat[i][j] = m.mat[i][j] + mat[i][j];
			}
		}
	}

	return a;
}

matrix matrix::operator-(matrix m)
{
	matrix a(row,col);
	if(m.getrow()!=row || m.getcol()!=col)
	{
		std::cout << "invalid -  operation";
	}
	else
	{
		for(int i = 0 ; i < row ; i++)
		{
			for(int j=0 ; j<col ; j++)
			{
				a.mat[i][j] = - m.mat[i][j] + mat[i][j];
			}
		}
	}

	return a;
}

matrix matrix::operator*(matrix m)
{
	matrix a(row,m.getcol());
	a.null();
	if(col != m.getrow())
	{
		std::cout << "Invalid * operation";
	}
	else
	{	
		for(int i=0; i < row; ++i)
		{
	        for(int j=0; j < m.getcol(); ++j)
	        {	
	            for(int k=0; k < col; ++k)
	            {
	                a.mat[i][j] += mat[i][k]*m.mat[k][j];
	            }
	        }
		}
	}
	return a;
}

matrix matrix::transpose()
{
	
	matrix a(row,col);

	for(int i = 0 ; i < row ; i++)
	{
		for(int j=0 ; j< col ; j++)
		{
			a.mat[i][j] = mat[j][i];
		}
	}
	
	return a;
}


float matrix::det(int n)
{
	float D = 0; // Initialize result
 
    //  Base case : if matrix contains single element
    if (n == 1)
        return mat[0][0];
 
    matrix temp(n,n); // To store cofactors
 
    int sign = 1;  // To store sign multiplier
 
     // Iterate for each element of first row
    for (int f = 0; f < n; f++)
    {
        // Getting Cofactor of mat[0][f]
        int i = 0, j = 0;
 
    // Looping for each element of the matrix
	    for (int r = 0; r < n; r++)
	    {
	        for (int c = 0; c < n; c++)
	        {
	            //  Copying into temporary matrix only those element
	            //  which are not in given row and column
	            if (r != 0 && c != f)
	            {
	                temp.mat[i][j++] = mat[r][c];
	 
	                // Row is filled, so increase row index and
	                // reset col index
	                if (j == n - 1)
	                {
	                    j = 0;
	                    i++;
	                }
	            }
	        }
	    }
        D += sign * mat[0][f] * temp.det(n - 1);
 
        // terms are to be added with alternate sign
        sign = -sign;
    }
 
    return D;
}


matrix matrix::inv()
{
	if(row!=col)
	{
		std::cout << "invalid matrix for adjoint";
	}
	else
	{	float det = this->det(row);
		matrix a(row,row);
		matrix b(row,row);
		int n = row;
		for(int i = 0 ; i < row ; i++)
		{
			for(int j=0 ; j<col ; j++)
			{
				int i1= 0 ,j1 = 0;

				for (int r = 0; r < n; r++)
	    		{
			        for (int c = 0; c < n; c++)
			        {
			            //  Copying into temporary matrix only those element
			            //  which are not in given row and column
			            if (r != i && c != j)
			            {
			                b.mat[i1][j1++] = mat[r][c];
			 
			                // Row is filled, so increase row index and
			                // reset col index
			                if (j1 == n - 1)
			                {
			                    j1 = 0;
			                    i1++;
			                }
			            }
			        }
	    		}

	    		float d = b.det(i1);
	    		a.mat[i][j] = (pow(-1 , i+j)*d)/det;
			}
		}
		a.transpose();
		return a;
	}
}

matrix matrix::con_to_mtrx(float **a , int row , int col)
{
	matrix b(row,col);
	for(int i=0 ; i < row ; i++)
	{
		for( int j=0; j < col ; j++)
		{
			b.mat[i][j] = a[i][j];
			
		}
	}
	return b;
}