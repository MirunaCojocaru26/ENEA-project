#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "C:\Users\Miruna\Desktop\proiect ENEA\catch.hpp"
#include "C:\Users\Miruna\Desktop\proiect ENEA\Matrix.h"
#include "C:\Users\Miruna\Desktop\proiect ENEA\Matrix.cpp"
#include <fstream>
#include <vector>
using namespace std;

int equalmatrix(vector< vector <float>> a, vector< vector <float>> b)
{
    for(int i = 0; i < a.size() ; i++)
        for(int j = 0; j < a[i].size(); j++)
            if(a[i][j] != b[i][j])
                return 0;
    return 1;
}

TEST_CASE()
{
    ifstream fin("fisier.txt");//open a file
    int nr_lines_a,nr_columns_a,nr_lines_b,nr_columns_b;
    vector< vector <float> > a,b;

    //make first matrix for test
    fin>>nr_lines_a >> nr_columns_a;
    a.resize(nr_lines_a);
    for(int i = 0 ; i < nr_lines_a ; i++)
        a[i].resize(nr_columns_a);
    for(int i = 0 ; i < nr_lines_a ; i++)
        for(int j = 0; j < nr_columns_a; j++)
            fin>>a[i][j];

    //make second matrix for test
    fin>>nr_lines_b >> nr_columns_b;
    b.resize(nr_lines_b);
    for(int i = 0 ; i < nr_lines_b ; i++)
        b[i].resize(nr_columns_b);
    for(int i = 0 ; i < nr_lines_b ; i++)
        for(int j = 0; j < nr_columns_b; j++)
            fin>>b[i][j];

    //make the correct sum matrix
    int nr_lines_sum,nr_columns_sum;
    fin>>nr_lines_sum >> nr_columns_sum;
    vector< vector <float> > matrix_sum;
    matrix_sum.resize(nr_lines_sum);
    for(int i = 0; i < nr_lines_sum; i++)
        matrix_sum[i].resize(nr_columns_sum);
    for(int i = 0; i < nr_lines_sum; i++)
        for(int j = 0; j < nr_columns_sum; j++)
            fin>>matrix_sum[i][j];

    //multiply matrix
    int nr_lines_multiply,nr_columns_multiply;
    fin>>nr_lines_multiply >> nr_columns_multiply;
    vector< vector <float> > matrix_multiply;
    matrix_multiply.resize(nr_lines_multiply);
    for(int i = 0; i < nr_lines_multiply; i++)
        matrix_multiply[i].resize(nr_columns_multiply);
    for(int i = 0; i < nr_lines_multiply; i++)
        for(int j = 0; j < nr_columns_multiply; j++)
            fin>>matrix_multiply[i][j];

    //transposed matrix
    int nr_lines_transpos,nr_columns_transpos;
    fin>>nr_lines_transpos >> nr_columns_transpos;
    vector< vector <float> > matrix_transpos;
    matrix_transpos.resize(nr_lines_transpos);
    for(int i = 0; i < nr_lines_transpos; i++)
        matrix_transpos[i].resize(nr_columns_transpos);
    for(int i = 0; i < nr_lines_transpos; i++)
        for(int j = 0; j < nr_columns_transpos; j++)
            fin>>matrix_transpos[i][j];

    //adjacent matrix
    int nr_lines_star,nr_columns_star;
    fin>>nr_lines_star >> nr_columns_star;
    vector< vector <float> > matrix_star;
    matrix_star.resize(nr_lines_star);
    for(int i = 0; i < nr_lines_star; i++)
        matrix_star[i].resize(nr_columns_star);
    for(int i = 0; i < nr_lines_star; i++)
        for(int j = 0; j < nr_columns_star; j++)
            fin>>matrix_star[i][j];


    //make Matrix objects
    Matrix matrix_a(nr_lines_a,nr_columns_a,a);
    Matrix matrix_b(nr_lines_b,nr_columns_b,b);

    //tests
    REQUIRE( equalmatrix( matrix_a.getMatrix(), a) );
    REQUIRE( equalmatrix( (matrix_a + matrix_b).getMatrix(), matrix_sum) );
    REQUIRE( equalmatrix( (matrix_a * matrix_b).getMatrix(), matrix_multiply) );
    REQUIRE( matrix_a.determinant() == -105 );
    REQUIRE( matrix_b.determinant() == 51 );
    REQUIRE( equalmatrix( matrix_a.transposed().getMatrix(), matrix_transpos) );
    REQUIRE( equalmatrix( matrix_a.star().getMatrix(), matrix_star) );

    fin.close();
}
