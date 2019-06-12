#include <iostream>
#include <vector>
using namespace std;

class Matrix
{
protected:
    int number_lines, number_columns;
    vector< vector< float > > matrix;
public:
    Matrix();
    Matrix(float,float);
    friend istream& operator>> (istream& in, Matrix&x);
    friend ostream& operator<< (ostream& out, Matrix&x);
    Matrix& operator= (Matrix&x);
    Matrix& operator+ (Matrix&x);
    Matrix& operator* (Matrix&x);
    float determinant();
    Matrix& transposed();
    ~Matrix();
};

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

istream& operator>> (istream& in, Matrix&x)
{
    cout << "Number of lines: ";
    in >> x.number_lines;
    cout << "Number of columns: ";
    in >> x.number_columns;
    cout << "Matrix: ";
    x.matrix.resize(x.number_lines);
    for(int i = 0 ; i < x.number_lines ; i++)
        x.matrix[i].resize(x.number_columns);
    for(int i = 0 ; i < x.number_lines ; i++)
        for(int j = 0 ; j < x.number_columns ; j++)
            in >> x.matrix[i][j];
    return in;
}

ostream& operator<< (ostream& out, Matrix& x)
{
    for(int i = 0 ; i < x.number_lines ; i++)
    {
        for(int j = 0 ; j < x.number_columns ; j++)
            out << x.matrix[i][j]<<" ";
        out<<endl;
    }
    return out;
}

Matrix& Matrix::operator= (Matrix &x)
{
    if(this != &x)
    {
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
        cout << "The number of lines and columns of the two matrices do not match";
    else
    {
        for(int i = 0 ; i < x.number_lines ; i++)
            for(int j = 0 ; j < x.number_columns ; j++)
                (*aux).matrix[i][j] = matrix[i][j] + x.matrix[i][j];
    }
    return *aux;
}

Matrix& Matrix::operator* (Matrix &x)
{
    Matrix *aux = new Matrix(number_lines,x.number_columns);
    if(number_columns != x.number_lines)
        cout << "The number of lines from the first matrix must be equal with the number of columns from second matrix";
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
        cout<<"Number of line must be equal with number of columns";
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
                cout<<"+ "<< s<<endl;
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
                cout<<"- "<< s<<endl;
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

Matrix::~Matrix()
{
    number_lines = 0;
    number_columns = 0;
}

int main()
{
    Matrix a,b,c;
    cin>>a;
    cout<<a;
    cout<<a.transposed();
    return 0;
}
