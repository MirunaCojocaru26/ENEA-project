#include <iostream>
#include "Matrix.h"
#include <math.h>
#include <vector>

//constructor without parameters
Matrix::Matrix ()
{
    number_lines = 0;
    number_lines = 0;
}

//constructor with two parameters
Matrix::Matrix (int lines, int columns)
{
    number_lines = lines;
    number_columns = columns;
    matrix.resize(number_lines);
    for(int i = 0 ; i < number_lines ; i++)
        matrix[i].resize(number_columns);
}

//constructor with three parameters
Matrix::Matrix(int lines,int columns, std::vector< std::vector <float> > a)
{
    number_lines = lines;
    number_columns = columns;
    matrix.resize(number_lines);
    for(int i = 0 ; i < number_lines ; i++)
        matrix[i].resize(number_columns);
    for(int i = 0 ; i < number_lines ; i++)
        for(int j = 0 ; j < number_columns ; j++)
            matrix[i][j]=a[i][j];
}

//the cin of the class
std::istream& operator>> (std::istream& in, Matrix&x)
{
    std::cout << "Number of lines: ";
    in >> x.number_lines;
    std::cout << "Number of columns: ";
    in >> x.number_columns;
    std::cout << "Matrix: ";
    x.matrix.resize(x.number_lines);
    for(int i = 0 ; i < x.number_lines ; i++)
        x.matrix[i].resize(x.number_columns);
    for(int i = 0 ; i < x.number_lines ; i++)
        for(int j = 0 ; j < x.number_columns ; j++)
            in >> x.matrix[i][j];
    return in;
}

//the cout of the class
std::ostream& operator<< (std::ostream& out, Matrix& x)
{
    for(int i = 0 ; i < x.number_lines ; i++)
    {
        for(int j = 0 ; j < x.number_columns ; j++)
            out << x.matrix[i][j]<<" ";
        out<<std::endl;
    }
    return out;
}

//equal operator
Matrix& Matrix::operator= (Matrix &x)
{
    if(this != &x) //I check the first time if I don't try to put my object in himself
    {
        for(int i = 0 ; i < x.number_lines ; i++) //I clean the object in case it wasn't new
            matrix[i].clear();
        matrix.clear();
        //I copy everything
        number_lines = x.number_lines;
        number_columns = x.number_columns;
        matrix.resize(x.number_lines);
        for(int i = 0 ; i < x.number_lines ; i++)
            matrix[i].resize(x.number_columns);
        for(int i = 0 ; i < x.number_lines ; i++)
            for(int j = 0 ; j < x.number_columns ; j++)
                matrix[i][j] = x.matrix[i][j];
    }
    return *this;
}

//the assembly operator
Matrix& Matrix::operator+ (Matrix &x)
{
    Matrix *aux = new Matrix(number_lines,number_columns);
    if(x.number_columns != number_columns || x.number_lines != number_lines)
        throw 0; //stops the function if the matrices have different sizes and can not be added
    else
    {
        //add the elements of the matrices one by one
        for(int i = 0 ; i < x.number_lines ; i++)
            for(int j = 0 ; j < x.number_columns ; j++)
                (*aux).matrix[i][j] = matrix[i][j] + x.matrix[i][j];
        return *aux;
    }
}

//the multiplication operator
Matrix& Matrix::operator* (Matrix &x)
{
    Matrix *aux = new Matrix(number_lines,x.number_columns);
    if(number_columns != x.number_lines)
        throw 2; //stops the function if the matrices have different sizes and can not be multiply
    else
    {
        for(int i = 0 ; i < number_lines ; i++) //I'm going through the first matrix on the lines
            for(int j = 0 ; j < x.number_columns ; j++) //and the second on the columns
            {
                float s = 0;
                for(int h = 0 ; h < number_columns ; h++) //I multiply the first matrix line with the second matrix column
                    s = s + matrix[i][h] * x.matrix[h][j]; //and add the results
                (*aux).matrix[i][j] = s;
            }
    }
    return *aux;
}

//getter for matrix
std::vector < std::vector <float>> Matrix::getMatrix()
{
    return matrix;
}

//calculating the determinant of a matrix
float Matrix::determinant()
{
    if(number_columns != number_lines)
        throw 3;
    float *det = new float;
    (*det)=0;
    Matrix *aux = new Matrix(number_lines-1,number_columns-1);
    // when I reach at a matrix of 2x2 I can calculate the determinant
    //(or 3x3, but it was more complicated and I like to simplify things as much as I can)
    if(number_lines == 2)
        return ((matrix[0][0] * matrix[1][1]) - (matrix[1][0] * matrix[0][1]));
    else
    {
        //because my matrix has more than 2 lines and 2 columns, I make a first-line development to get matrices with one smaller
        for (int x = 0; x < number_columns; x++)
        {
            int subi = 0;
            //I build each smaller matrix
            for (int i = 1; i < number_lines; i++)
            {
                int subj = 0;
                for (int j = 0; j < number_lines; j++)
                    if (j != x) //for the new array, I delete line 0 and column x that I find myself at the moment
                    {
                        (*aux).matrix[subi][subj] = matrix[i][j];
                        subj++;
                    }
                subi++;
            }
            //I calculate the determinant until now and recursively call for the next matrix
            (*det) = (*det) + (pow(-1, x) * matrix[0][x] * (*aux).determinant());
        }
    }
    return (*det);
}

//calculating the transposed matrix
Matrix& Matrix::transposed()
{
    Matrix *aux = new Matrix(number_columns,number_lines);
    for(int i = 0 ; i < number_columns ; i++)
        for(int j = 0 ; j < number_lines ; j++)
            (*aux).matrix[i][j]=matrix[j][i]; //just switch the lines with the columns
    return *aux;
}

//calculating the adjacent matrix
Matrix& Matrix::star()
{
    Matrix *matrix_star = new Matrix(number_columns,number_lines);
    if( number_columns != number_lines )
        throw 3; //stops the function if the matrices have different sizes
    else
    {
        for(int i = 0 ; i < number_lines ; i++) //for every element in my matrix
            for(int j = 0 ; j < number_columns ; j++) //i calculate his partner in the adjacent matrix
            {
                //I build a new matrix without line i and column j in my matrix (the position of the element I want to find)
                Matrix *aux = new Matrix(number_columns-1,number_lines-1);
                for(int a=0, x=0; x < number_lines-1 ; a++, x++ )
                    for(int b=0, y=0; y < number_lines-1 ; b++, y++ )
                    {
                        if(a == i) //jump over line i
                            a++;
                        if(b == j) // jump ober column j
                            b++;
                        (*aux).matrix[x][y] = matrix[a][b];
                    }
                //and to find out, I just need to find the determinant of the new matrix
                float det = (*aux).determinant();
                //and to put him in the adjacent matrix
                if( (i + j) % 2 == 0 )
                    (*matrix_star).matrix[i][j] = det;
                else (*matrix_star).matrix[i][j] = -det;
            }
        return *matrix_star;
    }
}

//calculate the reversed matrix
//I wrote functions for everything I needed, so this feature is for calls only
Matrix& Matrix::reversed()
{
    //I built new matrices with the help of the carol to call up the functions
    Matrix *matrix_transposed = new Matrix(number_columns,number_lines);
    Matrix *matrix_star = new Matrix(number_columns,number_lines);
    Matrix *matrix_reversed = new Matrix(number_columns,number_lines);
    float det = this->determinant();// determinant call
    ///if the determinant is 0, my matrix hasn't reversed
    if(det != 0)
    {
        (*matrix_transposed) = this->transposed(); //transposed call
        (*matrix_star) = (*matrix_transposed).star(); //adjacent call
        //in the end I have to multiply the entire matrix by 1 / determinant
        for(int i = 0 ; i < number_lines ; i++)
            for(int j = 0 ; j < number_columns ; j++)
                (*matrix_reversed).matrix[i][j] = float( (*matrix_star).matrix[i][j] ) / det;
    }
    else
        throw 1; ///so I stop the function
    return *matrix_reversed;
}
