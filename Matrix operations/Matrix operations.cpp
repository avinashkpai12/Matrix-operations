// Matrix operations.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "matrix.h"

template <typename T>
void PrintMatrix(Matrix<T> mat)
{
    int nRows = mat.GetRowSize();
    int nCols = mat.GetColumnSize();
    for (int r = 0;r < nRows;r++)
    {
        for (int c = 0;c < nCols;c++)
        {
            std::cout << mat.GetElement(r, c) << " ";
        }
        std::cout << std::endl;
    }
}

int main()
{
    std::cout << "Code to test Matrix library!" << std::endl;
   
    double data[12] = {1.0, 2.0, 3.0,4.0, 
                       5.0, 6.0, 7.0, 8.0,
                       9.0, 10.0, 11.0, 12.0};

    Matrix<double> testMatrix(3, 4, data);


    //std::cout << testMatrix << std::endl;

    //Test the matrix elements print
    std::cout << std::endl << "***************************" << std::endl;
    std::cout << "3x4 matrix" << std::endl;
    PrintMatrix(testMatrix);
   
    /******************************************************************/
    // Testing element retrieval
    std::cout << std::endl << "***************************" << std::endl;
    std::cout << "Testing element retrieval" <<std::endl;
    std::cout << "Element[0,0] = " << testMatrix.GetElement(0, 0) << std::endl;
    std::cout << "Element[0,1] = " << testMatrix.GetElement(0, 1) << std::endl;
    std::cout << "Element[2,0] = " << testMatrix.GetElement(2, 0) << std::endl;
    std::cout << "Element[2,1] = " << testMatrix.GetElement(2, 1) << std::endl;
    std::cout << "Element[1,1] = " << testMatrix.GetElement(1, 1) << std::endl;
    std::cout << "Element[10,0] = " << testMatrix.GetElement(10, 0) << std::endl;

    /********************************************************************/
    //Testing Matrix Multiplication
    std::cout << std::endl << "***************************" << std::endl;
    std::cout << "Testing Matrix Multiplication" << std::endl;

    double testData[12] = { 1.0, 2.0, 3.0,
                            4.0, 5.0, 6.0,
                            7.0, 8.0, 9.0,
                            10.0, 11.0, 12.0 };

    Matrix<double> testMatrix2(4, 3, testData);
    std::cout << std::endl << "***************************" << std::endl;
    std::cout << "4x4 matrix" << std::endl;
    PrintMatrix(testMatrix2);
    std::cout << "Matrix multiplication (testMatrix x testMatrix2) = " << std::endl;
    Matrix<double> mulResult = testMatrix * testMatrix2;
    PrintMatrix(mulResult);
    std::cout << std::endl << "***************************" << std::endl;
    std::cout << "reverse the order of multiplication (testMatrix2 x testMatrix)" << std::endl;
    Matrix<double> mulResult2 = testMatrix2 * testMatrix;
    PrintMatrix(mulResult2);

    std::cout << std::endl << "***************************" << std::endl;
    std::cout << "Testing row vector multiplication with matrix " << std::endl;
    double rowVec[3] = { 2.4, 3.7, 1.9 };
    Matrix<double> rowV(1, 3, rowVec);
    PrintMatrix(rowV);
    std::cout << "Row Vector x testMatrix" << std::endl;
    Matrix<double> mulResult3 = rowV * testMatrix ; // (1 x 3) * (3 x 4)
    // (3 x 4) * (1 x 3)
    PrintMatrix(mulResult3);

    std::cout << std::endl << "***************************" << std::endl;
    std::cout << "Testing Matrix transpose " << std::endl;
    Matrix<double> transposeMat =  testMatrix.transposeMatrix();
    PrintMatrix(transposeMat);

    std::cout << std::endl << "***************************" << std::endl;
    std::cout << "Testing Matrix transpose with Same matrix " << std::endl;
    testMatrix.transposeSameMatrix();
    PrintMatrix(testMatrix);

}

