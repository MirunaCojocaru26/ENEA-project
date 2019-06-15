#include <iostream>
#include <vector>
#include "Matrix.h"
#include "Matrix.cpp"

using namespace std;

int main()
{
    Matrix raluca;
    cin>>raluca;
    cout<<raluca.star();
    try
    {
        cout<<"1. The sum of two matrices" << endl;
        cout<<"2. Multiplying two matrices" << endl;
        cout<<"3. Determinant of a matrix" << endl;
        cout<<"4. Transposed of a matrix" << endl;
        cout<<"5. Reverse matrix" << endl;
        cout<<"6. Exit" << endl;
        int x=1;
        Matrix matrix1,matrix2;
        while(x < 7 && x > 0)
        {
            cout<<"Case=";
            cin>>x;
            switch(x)
            {
                case 1:{
                    cin>>matrix1 >> matrix2;
                    cout<<matrix1 + matrix2 << endl;
                    break;
                }
                case 2:{
                    cin>>matrix1 >> matrix2;
                    cout<<matrix1 * matrix2 << endl;
                    break;
                }
                case 3:{
                    cin>>matrix1;
                    cout<<matrix1.determinant() << endl;
                    break;
                }
                case 4:{
                    cin>>matrix1;
                    cout<<matrix1.transposed() << endl;
                    break;
                }
                case 5:{
                    cin>>matrix1;
                    cout<<matrix1.reversed() << endl;
                    break;
                }
                case 6:{
                    x=10;
                    break;
                }
                default:{
                    cout<<"Don't find thise case. Try again" << endl;
                    break;
                }
            }
        }
    }
    catch( int e )
    {
        if( e == 0 )
            cout << "The number of lines and columns of the two matrices do not match";
        if( e == 1 )
            cout<<"The matrix is not invertible.";
        if( e == 2)
            cout << "The number of lines from the first matrix must be equal with the number of columns from second matrix";
        if( e == 3)
            cout<<"Number of line must be equal with number of columns";
    }
    return 0;
}
