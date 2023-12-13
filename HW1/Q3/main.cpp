#include "Matrix.hpp"

// Written by CHATGPT
int main()
{
    // Create matrices for testing
    Matrix<double> matrix1({{2.0, 0.0, -1.0},
                            {5.0, 1.0, .0},
                            {0.0, 1.0, 3.0}});

    Matrix<double> matrix2({{9.0, 8.0, 7.0},
                            {6.0, 5.0, 4.0},
                            {3.0, 2.0, 1.0}});

    // Test basic operations
    Matrix<double> result_add = matrix1 + matrix2;
    Matrix<double> result_subtract = matrix1 - matrix2;
    Matrix<double> result_multiply = matrix1 * matrix2;

    std::cout << "Matrix1 + Matrix2:" << std::endl
              << result_add << std::endl;
    std::cout << "Matrix1 - Matrix2:" << std::endl
              << result_subtract << std::endl;
    std::cout << "Matrix1 * Matrix2:" << std::endl
              << result_multiply << std::endl;

    // Test transpose
    Matrix<double> result_transpose = matrix1.transpose();
    std::cout << "Transpose of Matrix1:" << std::endl
              << result_transpose << std::endl;

    // Test inverse
    try
    {
        Matrix<double> result_inverse = matrix1.inverse();
        std::cout << "Inverse of Matrix1:" << std::endl
                  << result_inverse << std::endl;
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error calculating inverse: " << e.what() << std::endl;
    }

    // Test determinant
    try
    {
        double result_det = matrix1.determinant();
        std::cout << "Determinant of Matrix1: " << result_det << std::endl;
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error calculating determinant: " << e.what() << std::endl;
    }
    Matrix<double> dot = matrix1.dot(matrix2);
    std::cout << "Matrix1 dot Matrix2:" << std::endl
              << dot << std::endl;
    return 0;
}
