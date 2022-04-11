/*
 * AUTHORS: Wissam kabha
 * gitHub: https://github.com/Wissam111
 * Date: 03/2022
 */

#include "Matrix.hpp"

namespace zich
{

    Matrix::Matrix(const vector<double> &vec, int row, int col)
    {
        if ((row <= 0 || col <= 0) || vec.size() != row * col)
        {
            throw std::invalid_argument("Wrong cols and rows values");
        }

        this->_row = row;
        this->_col = col;

        unsigned int index = 0;
        for (int i = 0; i < row; i++)
        {
            for (int j = 0; j < col; j++)
            {
                _mat[i][j] = vec[index];
                index++;
            }
        }
    }

    /*
     * @brief  overloading a+b , a-b , --a , ++a , a++ , a--
     *         -a , a*Scalar , a*=Scalar , a*b , a+=b operators
     */

    Matrix Matrix::operator+(const Matrix &otherMat)
    {

        vector<double> new_vec;
        operation(otherMat, 0, new_vec, OPERATOR::plus);
        return Matrix(new_vec, _row, _col);
    }

    Matrix Matrix::operator-(const Matrix &otherMat)
    {
        vector<double> new_vec;
        operation(otherMat, 0, new_vec, OPERATOR::minus);
        return Matrix(new_vec, _row, _col);
    }
    Matrix Matrix::operator-()
    {
        vector<double> new_vec;
        // first arg doesnt matter
        operation(*this, 0, new_vec, OPERATOR::mutlNg1);
        return Matrix(new_vec, _row, _col);
    }
    Matrix Matrix::operator+()
    {
        vector<double> new_vec;
        operation(*this, 0, new_vec, OPERATOR::plusUnary);
        return Matrix(new_vec, _row, _col);
    }

    Matrix Matrix::operator++(int) // postfix a++
    {

        Matrix temp = *this;
        ++(*this);
        return temp;
    }
    Matrix Matrix::operator--(int) // postfix a--
    {
        Matrix temp = *this;
        --(*this);
        return temp;
    }

    Matrix &Matrix::operator++() // prefix ++a
    {
        vector<double> new_vec;
        operation(*this, 0, new_vec, plus1_left);
        return *this;
    }

    Matrix &Matrix::operator--() // prefix --a
    {
        vector<double> new_vec;
        operation(*this, 0, new_vec, minus1_left);
        return *this;
    }

    Matrix operator*(const double scalar, const Matrix &Mat)
    {

        Matrix m = Mat;
        std::vector<double> new_vec;
        m.operation(Mat, scalar, new_vec, sc_mult);
        return Matrix(new_vec, Mat._row, Mat._col);
    }
    Matrix operator*(const Matrix &Mat, const double scalar)
    {

        Matrix temp = Mat;
        temp = scalar * Mat;
        return temp;
    }

    Matrix &Matrix::operator*=(const double scalar)
    {

        *this = scalar * (*this);
        return *this;
    }

    Matrix &Matrix::operator+=(Matrix const &otherMat)
    {
        *this = *this + otherMat;
        return *this;
    }
    Matrix &Matrix ::operator-=(Matrix const &otherMat)
    {
        *this = *this - otherMat;
        return *this;
    }
    Matrix Matrix::operator*(Matrix const &otherMat)
    {
        vector<double> new_vec;
        operation(otherMat, 0, new_vec, OPERATOR::mult_mat);
        return Matrix(new_vec, _row, otherMat._col);
    }

    Matrix &Matrix ::operator*=(Matrix const &otherMat)
    {
        *this = *this * (otherMat);
        this->setRowCol(_row, otherMat._col);
        return *this;
    }

    /*
     * @brief  overloading compare operators
     *         == , != , > ,<, >= , <=
     */

    bool operator==(const Matrix &mat1, const Matrix &mat2)
    {
        return compare(mat1, mat2, COMPARE::EQUAL);
    }
    bool operator!=(const Matrix &mat1, const Matrix &mat2)
    {

        return !(mat1 == mat2);
    }

    bool operator>(const Matrix &mat1, const Matrix &mat2)
    {
        return compare(mat1, mat2, COMPARE::GREATER);
    }

    bool operator<(const Matrix &mat1, const Matrix &mat2)
    {
        return compare(mat1, mat2, COMPARE::SMALLER);
    }

    bool operator<=(const Matrix &mat1, const Matrix &mat2)
    {

        return !(mat1 > mat2);
    }
    bool operator>=(const Matrix &mat1, const Matrix &mat2)
    {

        return !(mat1 < mat2);
    }

    /*
     * @brief  overloading input/output
     */
    std::ostream &operator<<(std::ostream &output, const Matrix &matrix)
    {
        std::string m;
        for (int i = 0; i < matrix._row; i++)
        {

            m += "[";
            for (int j = 0; j < matrix._col - 1; j++)
            {
                int a = matrix._mat.at(i).at(j);
                m += std::to_string(a);
                m += " ";
            }
            int a = matrix._mat.at(i).at(matrix._col - 1);
            m += std::to_string(a);

            m += "]";
            if (i != matrix._row - 1)
            {
                m += "\n";
            }
        }
        output << m;

        return output;
    }

    std::istream &operator>>(std::istream &input, Matrix &matrix)
    {

        std::string buff;
        int rows_counter = 0;
        int cols_counter = 0;
        int count = 0;
        vector<double> tempVec;
        getline(input, buff);
        if (!input)
        {
            std::cout << "failure\n";
        }
        unsigned endOfString = buff.size() - 1;
        for (unsigned i = 0; i < buff.size(); i++)
        {

            if (buff[i] == '[')
            {
                count++;
            }
            if (((i == 0) && (buff[i] != '[')) || ((i == endOfString) && buff[i + 1] != '\0'))
            {
                throw std::invalid_argument("invalid operation on the matrix");
            }

            if (buff[i] == ']')
            {
                rows_counter++;
                if ((i < buff.size() - 1) && !(buff[i + 1] == ',' && buff[i + 2] == ' '))
                {
                    throw std::invalid_argument("invalid operation on the matrix");
                }
            }
            if (isdigit(buff[i]) != 0)
            {
                int a = buff[i] - '0';
                tempVec.push_back(a);
                if (count == 1)
                {
                    cols_counter++;
                }
            }
        }

        Matrix tempMat = {tempVec,
                          rows_counter,
                          cols_counter};

        matrix = tempMat;

        return input;
    }

    /*
     * @brief fucntion that handle +,- , etc operators
     */
    void Matrix::operation(const Matrix &otherMat, double scalar, vector<double> &new_vec, OPERATOR opr)
    {
        if (!checkValidation(*this, otherMat, opr))
        {
            throw std::invalid_argument("invalid operation on the matrix");
        }

        unsigned int index = 0;
        double a = 0;
        double b = 0;
        for (int i = 0; i < _row; i++)
        {
            for (int j = 0; j < _col; j++)
            {

                switch (opr)
                {
                case plus:
                    a = this->_mat.at(i).at(j);
                    b = otherMat._mat.at(i).at(j);
                    new_vec.push_back(a + b);
                    break;
                case minus:
                    a = this->_mat.at(i).at(j);
                    b = otherMat._mat.at(i).at(j);
                    new_vec.push_back(a - b);
                    break;
                case mutlNg1:
                    new_vec.push_back((-1) * _mat[i][j]);
                    break;
                case minus1_left:
                    --_mat[i][j];
                    break;

                case plus1_left:
                    ++_mat[i][j];
                    break;

                case sc_mult:
                    new_vec.push_back(scalar * _mat.at(i).at(j));
                    break;
                case mult_mat:
                    mulMat(*this, otherMat, new_vec);
                    return;
                case plusUnary:
                    new_vec.push_back(_mat[i][j]);
                    break;

                default:
                    break;
                }
            }
        }
    }

    /*
     * @brief fucntion that handle compare  operators
     */
    bool compare(const Matrix &mat1, const Matrix &mat2, COMPARE cmp)
    {
        if (!checkValidation(mat1, mat2, chComp))
        {
            throw std::invalid_argument("invalid operation on the matrix");
        }

        double m1 = 0;
        double m2 = 0;
        for (int i = 0; i < mat1._row; i++)
        {
            for (int j = 0; j < mat1._col; j++)
            {
                m1 = mat1._mat.at(i).at(j);
                m2 = mat2._mat.at(i).at(j);

                switch (cmp)
                {
                case EQUAL:

                    if (m1 != m2)
                    {
                        return false;
                    }
                    break;
                case GREATER:
                    if (sumMat(mat1) > sumMat(mat2))
                    {
                        return true;
                    }
                    return false;
                case SMALLER:
                    if (sumMat(mat1) < sumMat(mat2))
                    {
                        return true;
                    }
                    return false;
                default:
                    break;
                }
            }
        }
        return true;
    }

    /*
     * @brief calculate the sum of matrix
     */
    int sumMat(const Matrix &mat)
    {

        int sum = 0;
        for (int i = 0; i < mat._row; i++)
        {
            for (int j = 0; j < mat._col; j++)
            {
                sum += mat._mat.at(i).at(j);
            }
        }
        return sum;
    }

    /*
     * @brief calculate the multiplication of two matrix
     */
    void mulMat(const Matrix &mat1, const Matrix &mat2, vector<double> &result)
    {

        // n*m m*k => n*k
        if (mat2._row != mat1._col)
        {
            throw std::invalid_argument("invalid operation on the matrix");
        }

        for (int i = 0; i < mat1._row; i++)
        {
            for (int j = 0; j < mat2._col; j++)
            {

                double temp = 0;
                for (int k = 0; k < mat2._row; k++)
                {

                    temp += mat1._mat.at(i).at(k) * mat2._mat.at(k).at(j);
                }

                result.push_back(temp);
            }
        }
    }
    /*
     * @brief check valdation of an input
     */
    bool checkValidation(const Matrix &mat1, const Matrix &mat2, OPERATOR opr)
    { // n*m m*k
        if ((opr == plus || opr == minus || opr == chComp) && ((mat1._col != mat2._col) || (mat1._row != mat2._row)))
        {
            return false;
        }

        if (opr == mult_mat && mat1._col != mat2._row)
        {
            return false;
        }

        return true;
    }
}