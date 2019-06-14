#include <iostream>
#include "Matrix.h"

Matrix::Matrix ()
{
    number_lines = 0;
    number_lines = 0;
}

Matrix::Matrix (float lines, float columns)
{
    number_lines = lines;
    number_columns = columns;
    matrix.resize(number_lines);
    for(int i = 0 ; i < number_lines ; ++i)
        matrix[i].resize(number_columns);
}

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

Matrix& Matrix::operator= (Matrix &x)
{
    if(this != &x)
    {
        for(int i = 0 ; i < x.number_lines ; i++)
            matrix[i].clear();
        matrix.clear();
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

Matrix& Matrix::operator+ (Matrix &x)
{
    Matrix *aux = new Matrix(number_lines,number_columns);
    if(x.number_columns != number_columns || x.number_lines != number_lines)
        throw 0;
    else
    {
        for(int i = 0 ; i < x.number_lines ; i++)
            for(int j = 0 ; j < x.number_columns ; j++)
                (*aux).matrix[i][j] = matrix[i][j] + x.matrix[i][j];
        return *aux;
    }
}

Matrix& Matrix::operator* (Matrix &x)
{
    Matrix *aux = new Matrix(number_lines,x.number_columns);
    if(number_columns != x.number_lines)
        throw 2;
    else
    {
        for(int i = 0 ; i < number_lines ; i++)
            for(int j = 0 ; j < x.number_columns ; j++)
            {
                float s = 0;
                for(int h = 0 ; h < number_columns ; h++)
                    s = s + matrix[i][h] * x.matrix[h][j];
                (*aux).matrix[i][j] = s;
            }
    }
    return *aux;
}

float Matrix::determinant()
{
    float *det = new float;
    (*det) = 0;
    if(number_columns != number_lines)
        throw 3;
    else
    {
        if(number_lines == 2)
            (*det) = matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];
        else
        {
            for(int i = 0 ; i < number_lines ; i++)
            {
                float s = 1;
                int h, j, f;
                for(h = i , j = 0 ; h < number_lines && j < number_columns ; h++ , j++)
                    s = s * matrix[h][j];
                for(h = 0 , f = j ; h < number_lines && f < number_columns ; h++ , f++)
                    s = s * matrix[h][f];
                (*det) = (*det) + s;
            }
            for(int i = number_lines-1 ; i >= 0 ; i--)
            {
                float s = 1;
                int h, j, f;
                for(h = i , j = number_columns-1 ; h < number_lines && j >= 0 ; h++ , j--)
                    s = s * matrix[h][j];
                for(h = 0 , f = j ; h < number_lines && f >= 0 ; h++ , f--)
                    s = s * matrix[h][f];
                (*det) = (*det) - s;
            }
        }
    }
    return *det;
}

Matrix& Matrix::transposed()
{
    Matrix *aux = new Matrix(number_columns,number_lines);
    for(int i = 0 ; i < number_columns ; i++)
        for(int j = 0 ; j < number_lines ; j++)
            (*aux).matrix[i][j]=matrix[j][i];
    return *aux;
}

Matrix& Matrix::star()
{
    Matrix *matrix_star = new Matrix(number_columns,number_lines);
    if( number_columns != number_lines )
        throw 3;
    else
    {
        for(int i = 0 ; i < number_lines ; i++)
            for(int j = 0 ; j < number_columns ; j++)
            {
                Matrix *aux = new Matrix(number_columns-1,number_lines-1);
                for(int a=0, x=0; x < number_lines-1 ; a++, x++ )
                    for(int b=0, y=0; y < number_lines-1 ; b++, y++ )
                    {
                        if(a == i)
                            a++;
                        if(b == j)
                            b++;
                        (*aux).matrix[x][y] = matrix[a][b];
                    }
                float det = (*aux).determinant();
                if( (i + j) % 2 == 0 )
                    (*matrix_star).matrix[i][j] = det;
                else (*matrix_star).matrix[i][j] = -det;
            }
        return *matrix_star;
    }
}

Matrix& Matrix::reversed()
{
    Matrix *matricea_transpusa = new Matrix(number_columns,number_lines);
    Matrix *matricea_star = new Matrix(number_columns,number_lines);
    Matrix *matricea_inversa = new Matrix(number_columns,number_lines);
    float det = this->determinant();
    if(det != 0)
    {
        (*matricea_transpusa) = this->transposed();
        (*matricea_star) = (*matricea_transpusa).star();
        for(int i = 0 ; i < number_lines ; i++)
            for(int j = 0 ; j < number_columns ; j++)
                (*matricea_inversa).matrix[i][j] = float( (*matricea_star).matrix[i][j] ) / det;
    }
    else
        throw 1;
    return *matricea_inversa;
}
