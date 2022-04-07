/*
 * AUTHORS: Wissam kabha
 * gitHub: https://github.com/Wissam111
 * Date: 03/2022
 */
#include "Matrix.hpp"
#include "doctest.h"
#include <string>
#include <iostream>
using namespace std;
using namespace zich;
#include <algorithm>
#include <time.h>

//----------- Generating random Matrix her value between [min ,max] ----------//
Matrix generateRandomMatrix(int row, int col, int max, int min)
{
    vector<double> vec;
    int randNum;
    for (int i = 0; i < row * col; i++)
    {
        randNum = rand() % (max - min + 1) + min;
        vec.push_back(randNum);
    }

    return Matrix(vec, row, col);
}

//----------- Test handling for diffrent operators ----------//
bool checkOper(Matrix &mat1, Matrix &mat2, Matrix &mat, int row, int col, OPERATOR opr)
{

    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {

            switch (opr)
            {
            case OPERATOR::plus:
            {

                if ((mat1.getAt(i, j) + mat2.getAt(i, j)) != mat.getAt(i, j))
                {
                    return false;
                }
                break;
            }
            case OPERATOR::minus:
            {
                if ((mat1.getAt(i, j) - mat2.getAt(i, j)) != mat.getAt(i, j))
                {
                    return false;
                }
                break;
            }
            // checks all --a , a-- , ++a , a++
            case OPERATOR::minus1_left:
            {
                int temp = mat1.getAt(i, j) - mat.getAt(i, j);

                if (abs(temp) != 1)
                {
                    return false;
                }
                break;
            }
            case OPERATOR::mutlNg1:
            {
                int temp = mat1.getAt(i, j);

                if (-1 * temp != mat.getAt(i, j))
                {
                    return false;
                }
                break;
            }
            case OPERATOR::sc_mult:
            {
                int temp = mat1.getAt(i, j);

                if (temp != 3 * mat.getAt(i, j))
                {
                    return false;
                }
                break;
            }
            case OPERATOR::mult_mat:
            {
                if (mat1.getAt(i, j) != mat.getAt(i, j))
                {
                    return false;
                }
                break;
            }

            default:
                cout << "hoxfox" << endl;
                break;
            }
        }
    }
    return true;
}

//----------- Test not valid Operations ----------//
TEST_CASE("not valid  input test case")

{ // n*m m*k

    vector<double> v1 = {1, 0, 0, 0, 1, 0, 0, 0, 1};
    vector<double> v2 = {3, 0, 0,
                         0, 3, 0,
                         0, 0, 3,
                         5, 4, 3};

    CHECK_THROWS(Matrix(v1, -3, 3));
    CHECK_THROWS(Matrix(v2, 2, -3));
    CHECK_THROWS(Matrix(v2, -2, -3));
    CHECK_THROWS(Matrix(v2, 3, 5));
    CHECK_THROWS(Matrix(v2, 4, 4));

    Matrix m1{v1, 3, 3};
    Matrix m2{v2, 4, 3};
    for (int i = 1; i < 100; i++)
    {
        for (int j = i + 1; j < 100; j++)
        {
            bool res;
            m1.setRowCol(i, i);
            m2.setRowCol(j, j);
            CHECK_THROWS(m1 * m2);
            CHECK_THROWS(m1 + m2);
            CHECK_THROWS(m1 - m2);
            CHECK_THROWS(res = (m1 <= m2));
            CHECK_THROWS(res = (m1 >= m2));
            CHECK_THROWS(res = (m1 == m2));
            CHECK_THROWS(res = (m1 != m2));
            CHECK_THROWS(res = (m1 > m2));
            CHECK_THROWS(res = (m1 < m2));
        }
    }
}

//----------- Test all Compare Operators ----------//
TEST_CASE("Test compare")
{

    Matrix m1 = generateRandomMatrix(3, 3, 100, 50);

    for (int i = 1; i < 50; i++)
    {
        //[50,100]
        Matrix m1 = generateRandomMatrix(i, i, 100, 50);
        //[150,200]
        Matrix m2 = generateRandomMatrix(i, i, 200, 150);

        CHECK((m1 > m2) == false);
        CHECK((m1 >= m2) == false);
        CHECK((m1 <= m2) == true);
        CHECK((m1 < m2) == true);
        CHECK((m1 != m2) == true);
        CHECK((m1 == m2) == false);
        CHECK((m1 == m1) == true);
    }
}
TEST_CASE("Test operators")
{

    for (int i = 1; i < 20; i++)
    {
        Matrix m1 = generateRandomMatrix(i, i, 100, 50);
        Matrix m2 = generateRandomMatrix(i, i, 200, 150);
        Matrix mPlus = m1 + m2;
        Matrix mMinus = m1 - m2;
        //----------- Test a+b Operator ----------//
        bool b1 = checkOper(m1, m2, mPlus, i, i, OPERATOR::plus);
        //----------- Test a-b Operator ----------//
        bool b2 = checkOper(m1, m2, mMinus, i, i, OPERATOR::minus);
        //----------- Test --a Operator ----------//
        Matrix m3 = m1;
        Matrix m1left = --m1;
        bool b3 = checkOper(m3, m3, m1left, i, i, OPERATOR::minus1_left);

        //----------- Test ++a Operator ----------//
        Matrix p1left = ++m1left;
        ++p1left;
        bool b4 = checkOper(m3, m3, p1left, i, i, OPERATOR::minus1_left);

        //----------- Test -a Operator ----------//
        Matrix m1Neg = -p1left;
        bool b5 = checkOper(m1Neg, m1Neg, p1left, i, i, OPERATOR::mutlNg1);

        //----------- Test Scalar*a Operator ----------//
        Matrix mutlSc = 3 * m1Neg;
        bool b6 = checkOper(mutlSc, mutlSc, m1Neg, i, i, OPERATOR::sc_mult);

        //----------- Test += Operator ----------//
        // plus testcase same as plusEqual
        Matrix oldPlusM1 = m1;
        m1 += m2;

        bool b8 = checkOper(oldPlusM1, m2, m1, i, i, OPERATOR::plus);

        //----------- Test -= Operator ----------//
        // plus testcase same as plusEqual
        Matrix oldMinusM1 = m1;
        m1 -= m2;
        bool b9 = checkOper(oldMinusM1, m2, m1, i, i, OPERATOR::minus);
        //-------------------------------------//
        CHECK(b1 == true);
        CHECK(b2 == true);
        CHECK(b3 == true);
        CHECK(b4 == true);
        CHECK(b5 == true);
        CHECK(b6 == true);
        CHECK(b8 == true);
        CHECK(b9 == true);
    }
    //----------- Test a*b Operator ----------//
    vector<double> v1 = {1, 0, 4, 12, 1, 0, 1, 6, 1};
    vector<double> v2 = {3, 0, 5, 0, 3, 1, 0, 5, 3};
    vector<double> resMul = {3, 20, 17, 36, 3, 61, 3, 23, 14};

    Matrix mu1{v1, 3, 3};
    Matrix mu2{v2, 3, 3};
    Matrix mres{resMul, 3, 3};
    Matrix mu = mu1 * mu2;

    bool b7 = checkOper(mu, mu, mres, 3, 3, OPERATOR::mult_mat);
    CHECK(b7 == true);
}
