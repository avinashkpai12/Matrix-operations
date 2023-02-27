//------------------------------------------------
//  File : matrix.h
//  Author : Avinash Pai
//  Organizarion : 
//--------------------------------------------------
//  Date    |  Developer  |  CLID | Description
//--------------------------------------------------
//          |             |       |   
//          |             |       |  
//          |             |       |
//          |             |       |              
//          |             |       |  
//--------------------------------------------------
/*
    This library is developed to help user perform operation on matrices.
    2D array structre in memory is stored linearly. Creating a 2D array
    will increase access operations instead creating a 1D linear array
    with rows and columns to mimic 2D array functionality.

    Tasks:
    1. Perform Matrix multiplication
        -- Matrix * Matrix
        -- Matrix * scalar
        -- scalar * Matrix
    2. Matrix transpose.
    Due to the ambiguity in data type, template is used.

    Steps:
    To use the Matrix library see the below steps
    1. Create an array type with data inserted
            double data[12] = {1.0, 2.0, 3.0,4.0,
                               5.0, 6.0, 7.0, 8.0,
                               9.0, 10.0, 11.0, 12.0};
    2. Matrix<double> testMatrix(3, 4, data); Use the command to create matrix
        and start performing operations
        Multiplication:
        -- Matrix * Matrix : ensure to have the correct dimensions i.e., 
                             (M x N) * (N x M). Otherwise result will be 0.
           
           To use matrix multiplication simply multiply the two matrices.
           ex : Matrix<double> mulResult = testMatrix * testMatrix2;
            where testMatrix and testMatrix2 are of the dimensions (3x4) and (4x3)
            respectively.
    3. Matrix Transpose. Added to funcitons 'tranposeMatrix' and 'transposeSameMatrix'.
        -- transposeMatrix : creates new matrix.
        -- transposeSameMatrix : reArranges the exiting matrix;

    Future Work:
    1. Load Matrix from a file. Use 2D array to create Matrix
    2. Use Ostream to replace PrintMatrix function
        ex std::cout << matrix << std::endl;
    3. Access Array elements using [][]. ex Matrix[].
    4. Can Add other operations.
    5. Adding Exception handling.
    6. Parallelize.

    
    Compilation instruction:
    g++ -o matrix main.c -std=c++11 (add or remove tests in main.c)
    Run :
    matrix..exe

*/
#ifndef Matrix_h
#define Matrix_h

#include <iostream>

template<typename T>
class Matrix
{
private:
    int rows, cols, n_elements;
    T* matrix;
private:
    int subIndex(int _row, int _col);
public:
    //Different constructor definitions
    Matrix();
    Matrix(int _rows, int _cols);
    Matrix(int _rows, int _cols, const T* data);
    Matrix(const Matrix<T>& inputMat);

    //Destructor
    ~Matrix();

    //Access the Elements using Getters
    T GetElement(int _row, int _col);
    bool setElement(int _row, int _col, T val);
    int GetRowSize();
    int GetColumnSize();

    //Transpose
    Matrix<T> transposeMatrix();
    void transposeSameMatrix();

    //overload operator * (friends)
    template<typename U> friend Matrix<U> operator* (const Matrix<U>& l, const Matrix<U>& r);
    template<typename U> friend Matrix<U> operator* (const U& l, const Matrix<U>& r);
    template<typename U> friend Matrix<U> operator* (const Matrix<U>& l, const U& r);

  
    //1. Future work
    /*friend std::ostream& operator<<(std::ostream& stream, const Matrix& other)
    {
        for (int r = 0;r < other.rows;r++)
        {
            for (int c = 0;c < other.cols ;c++)
            {
                stream << other.GetElement(r, c) << " ";
            }
            stream << std::endl;
        }
        return stream;
    }*/


};

/***************************************************
    Constructor / destructor functions
/****************************************************/
//1. Default Constructor
template <typename T>
Matrix<T>::Matrix()
{
    rows = 1;
    cols = 1;
    n_elements = 1;
    matrix = new T[n_elements];
    matrix[0] = 0.0;
}

//2. Construct an empty matrix with all 0 elements
template <typename T>
Matrix<T>::Matrix(int _rows, int _cols)
{
    rows = _rows;
    cols = _cols;
    n_elements = rows * cols;
    matrix = new T[n_elements];
    for (int i = 0;i < n_elements;i++)
        matrix[i] = 0.0;
}

//3. Construct from linear array
template <typename T>
Matrix<T>::Matrix(int _rows, int _cols, const T* data)
{
    rows = _rows;
    cols = _cols;
    n_elements = rows * cols;
    matrix = new T[n_elements];
    for (int i = 0;i < n_elements;i++)
        matrix[i] = data[i];
}

//3. Copy constructor
template <typename T>
Matrix<T>::Matrix(const Matrix<T>& inputMat)
{
    rows = inputMat.rows;
    cols = inputMat.cols;
    n_elements = inputMat.n_elements;
    matrix = new T[n_elements];
    for (int i = 0;i < n_elements;i++)
        matrix[i] = inputMat.matrix[i];

}

//destructor
template <typename T>
Matrix<T>::~Matrix()
{
    if (matrix != nullptr)
        delete[] matrix;
}

/***************************************************
    Element Functions
    return the element using row, column
    if row, column doesnt exist return ERROR or 0.0(for now)
/****************************************************/
template <typename T>
T Matrix<T>::GetElement(int _row, int _col)
{
    int index = subIndex(_row, _col);
    if (index >= 0)
        return matrix[index];
    else
        return 0.0;
}

template <typename T>
bool Matrix<T>::setElement(int _row, int _col, T elementVal)
{
    int index = subIndex(_row, _col);
    if (index >= 0)
    {
        matrix[index] = elementVal;
        return true;
    }
    else
        return false;
}

template <typename T>
int Matrix<T>::GetRowSize()
{
    return rows;
}

template <typename T>
int Matrix<T>::GetColumnSize()
{
    return cols;
}

/***************************************************
    Matrix transpose
/****************************************************/
template <typename T>
Matrix<T> Matrix<T>::transposeMatrix()
{
   

    int rowVal = this->rows;
    int colVal = this->cols;
    int nEle = rowVal * colVal;
    T* transpose = new T[nEle];
    int i = 0;
    for (int c = 0;c < colVal;c++)
    {
        
        for (int r = 0;r < rowVal;r++)
        {
            
            transpose[i] = this->GetElement(r, c);
            i++;
        }
    }

    Matrix<T> Transpose(colVal, rowVal, transpose);
    delete[] transpose;
    return Transpose;

}

template <typename T>
void Matrix<T>::transposeSameMatrix()
{
    int rowVal = this->rows;
    int colVal = this->cols;
    int nEle = rowVal * colVal;
    T* transpose = new T[nEle];
    int i = 0;
    for (int c = 0;c < colVal;c++)
    {

        for (int r = 0;r < rowVal;r++)
        {

            transpose[i] = this->GetElement(r, c);
            i++;
        }
    }

    //can implement this change as a 'reSize' function(Future work)
    //change row and col size
    this->rows = colVal;
    this->cols = rowVal;
    for (int i = 0;i < nEle;i++)
        this->matrix[i] = transpose[i];

    //clear the temp array
    delete[] transpose;

}

/***************************************************
    Overloaded operator *
/****************************************************/
//1. Scaler * matrix
template <typename U>
Matrix<U> operator *(const U& l, const Matrix<U>& r)
{
    int n_rows = r.rows;
    int n_cols = r.cols;
    int n_elements = r.n_elements;
    U* tempRes = new U[n_elements];
    for (int i = 0;i < n_elements;i++)
        tempRes[i] = l * r.matrix[i];

    Matrix<U> result(n_rows, n_cols, tempRes);
    delete[] tempRes;

    return result;
}

//2. Matrix *  scaler
template <typename U>
Matrix<U> operator *(const Matrix<U>& l, const U& r )
{
    int n_rows = l.rows;
    int n_cols = l.cols;
    int n_elements = l.n_elements;
    U* tempRes = new U[n_elements];
    for (int i = 0;i < n_elements;i++)
        tempRes[i] =  l.matrix[i] * r;

    Matrix<U> result(n_rows, n_cols, tempRes);
    delete[] tempRes;

    return result;
}

//3. Matrix * Matrix
template <typename T>
Matrix<T> operator *(const Matrix<T>& l, const Matrix<T>& r)
{   
    //get the number of rows and cols for each matrix
    int l_rows = l.rows; //3
    int l_cols = l.cols; //1
    int r_rows = r.rows; //3
    int r_cols = r.cols; //3

    //matrix multiplication will work when the matrices being multiplies have dim
    // for ex: (M x N) * (N x M)
    if (l_cols == r_rows)
    {
        //Standard matrix multiplication condition
        //result will be of size
        T* tempRes = new T[l.rows * r.cols];

        for (int lRow = 0;lRow < l_rows;lRow++)
        {
            for (int rCol = 0;rCol < r_cols;rCol++)
            {
                T result = 0.0;

                for (int lCol = 0; lCol < l_cols;lCol++)
                {
                    //compute l linear index
                    int l_linearIndex = (lRow * l_cols) + lCol;

                    //compute the r linear index
                    int r_linearIndex = (lCol * r_cols) + rCol;

                    result += l.matrix[l_linearIndex] + r.matrix[r_linearIndex];
                }

                //store the result
                int result_linearIndex = (lRow * r_cols) + rCol;
                tempRes[result_linearIndex] = result;
            }
        }
        Matrix<T> result(l_rows, r_cols, tempRes);
        delete[] tempRes;
        return result;

    }
    else 
    {
        Matrix<T> result(1, 1);
        return result;
    }

}

template <typename T>
int Matrix<T>::subIndex(int _row, int _col)
{
    if ((_row < rows) && (_row >= 0) && (_col < cols) && (_col >= 0))
        return (_row * cols) + _col;
    else
        return -1;
}



#endif // Matrix_h


