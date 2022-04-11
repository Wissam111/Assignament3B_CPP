
/*
 * AUTHORS: Wissam kabha
 * gitHub: https://github.com/Wissam111
 * Date: 03/2022
 */

#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <vector>
#include <string>
#include <map>
#include <algorithm>
using std::vector;
namespace zich
{

    enum OPERATOR
    {

        plus,        // a+b
        minus,       // a-b
        minus1_left, //--a
        plus1_left,  //++a
        mutlNg1,     //-a
        plusUnary,   //+a
        sc_mult,     // a*Scalar
        mult_mat,    // a*b
        chComp,
    };
    enum COMPARE
    {
        EQUAL,   // ==
        GREATER, // >
        SMALLER, // <
    };

    class Matrix
    {

    private:
        std::map<int, std::map<int, double>> _mat;
        int _row, _col;

    public:
        Matrix(const vector<double> &vec, int row, int col);
        ~Matrix(){};

        //--------------overloading input/output operators ---------------//
        friend std::ostream &operator<<(std::ostream &output, const Matrix &matrix);
        friend std::istream &operator>>(std::istream &input, Matrix &mat);

        //--------------overloading operators ---------------//
        Matrix operator+(const Matrix &otherMat);
        Matrix operator-(const Matrix &otherMat);
        Matrix operator-(); // minus onary
        Matrix operator+(); // plus onary
        Matrix &operator++();
        Matrix &operator--();
        Matrix operator++(int);
        Matrix operator--(int);
        friend Matrix operator*(const double scalar, const Matrix &mat);
        friend Matrix operator*(const Matrix &mat, const double scalar);
        Matrix &operator*=(const double scalar);
        Matrix &operator+=(Matrix const &otherMat);
        Matrix &operator-=(Matrix const &otherMat);
        Matrix operator*(Matrix const &otherMat);
        Matrix &operator*=(Matrix const &otherMat);

        //--------------help functions ---------------//
        friend bool compare(const Matrix &mat1, const Matrix &mat2, COMPARE cmp);
        friend int sumMat(const Matrix &mat);
        friend bool checkValidation(const Matrix &mat1, const Matrix &mat2, OPERATOR opr);
        void operation(const Matrix &otherMat, double scalar, vector<double> &new_vec, OPERATOR opr);
        friend void mulMat(const Matrix &mat1, const Matrix &mat2, vector<double> &result);
        // just for testing
        void setRowCol(int row, int col)
        {
            _col = col;
            _row = row;
        }
        double getAt(int i, int j)
        {
            return _mat[i][j];
        }
        //--------------compare operators ---------------//
        friend bool operator==(const Matrix &mat1, const Matrix &mat2);
        friend bool operator!=(const Matrix &mat1, const Matrix &mat2);
        friend bool operator>(const Matrix &mat1, const Matrix &mat2);
        friend bool operator<(const Matrix &mat1, const Matrix &mat2);
        friend bool operator<=(const Matrix &mat1, const Matrix &mat2);
        friend bool operator>=(const Matrix &mat1, const Matrix &mat2);
    };
};
