#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
using namespace std;

#include "sources/Matrix.cpp"

zich::Matrix generateRandomMatrix(int row, int col, int max, int min)
{
    vector<double> vec;
    int randNum;
    for (int i = 0; i < row * col; i++)
    {
        randNum = rand() % (max - min + 1) + min;
        vec.push_back(randNum);
    }

    return zich::Matrix(vec, row, col);
}
int main()
{

    // std::vector<double> identity = {1, 0, 0, 0, 1, 0, 0, 0, 1};
    // std::vector<double> arr = {2, 0, 0, 0, 2, 0, 0, 0, 2};

    int scalar = 2;
    // zich::Matrix a{identity, 3, 3};
    // zich::Matrix b{arr, 3, 3};
    int command = 0;
    cout << "Commands: " << endl;
    cout << "Choose 1 for a+b" << endl;
    cout << "Choose 2 for a-b" << endl;
    cout << "Choose 3 for a*b" << endl;
    cout << "Choose 4 for scalar*a" << endl;
    cout << "Choose 5 for a>b" << endl;
    cout << "Choose 6 for a<b" << endl;
    cout << "Choose 7 for a>=b" << endl;
    cout << "Choose 8 for a<=b" << endl;
    cout << "Choose 9 for a==b" << endl;
    cout << "Choose 10 for a!=b" << endl;

    zich::Matrix a = generateRandomMatrix(5, 5, 20, 50);
    //[150,200]
    zich::Matrix b = generateRandomMatrix(5, 5, 50, 70);

    cout << "First Mat: " << endl;
    cout << a << endl;

    cout << "Second Mat: " << endl;
    cout << b << endl;

    while (true)
    {

        cout << "Enter Command: " << endl;
        cin >> command;

        switch (command)
        {
        case 1:

            cout << a + b << endl;
            break;

        case 2:
            cout << a - b << endl;
            break;
        case 3:
            cout << a * b << endl;
            break;

        case 4:
            cout << (scalar * a) << endl;
            break;

        case 5:
            cout << (a > b) << endl;
            break;

        case 6:
            cout << (a < b) << endl;
            break;

        case 7:
            cout << (a == b) << endl;
            break;

        case 8:
            cout << (a != b) << endl;
            break;
        default:
            break;
        }
    }
}