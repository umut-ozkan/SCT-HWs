#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <vector>
#include <iostream>
#include <math.h> 

template <class T>
class Matrix
{
private:
    std::vector<std::vector<T>> matrix;
    int M;
    int N;

    Matrix getRow(int row) const {
        if (row >= this->M){
            throw std::invalid_argument("Invalid row index");
        }
        Matrix<T> copy = Matrix<T>(1, this->N);
        for (int i=0; i<this->N; i++){
            copy.matrix[0][i] = this->matrix[row][i];
        }
        return copy;
    }

    Matrix setRow(int row, Matrix<T> newRow){
        if (row >= this->M){
            throw std::invalid_argument("Invalid row index");
        }
        if (newRow.M != 1 || newRow.N != this->N){
            throw std::invalid_argument("Invalid row dimensions");
        }
        for (int i=0; i<this->N; i++){
            this->matrix[row][i] = newRow.matrix[0][i];
        }
        return *this;
    }

    Matrix swapRows(int row1, int row2){
        if (row1 >= this->M || row2 >= this->M || row1 < 0 || row2 < 0) {
            throw std::invalid_argument("Invalid row index");
        }
        Matrix<T> temp = this->getRow(row1);
        this->setRow(row1, this->getRow(row2));
        this->setRow(row2, temp);
        return *this;
    }   

public:
    Matrix(){
        this->M = 0;
        this->N = 0;
        this->matrix = std::vector<std::vector<T>>(0, std::vector<T>(0, 0));
    }

    Matrix(int rows, int columns, T value=0){
        this->M = rows;
        this->N = columns;
        this->matrix = std::vector<std::vector<T>>(rows, std::vector<T>(columns, value));
    }
    Matrix(const std::vector<std::vector<T>>& data){
        for(int i = 0; i < data.size(); i++){
            if(data[i].size() != data[0].size())
                throw std::invalid_argument("Invalid Matrix. Provide valid matrix.");
        }
        this->M = data.size();
        this->N = data[0].size();
        this->matrix = data;
    }

    Matrix inverse() {
    if (typeid(T) != typeid(float) && typeid(T) != typeid(double))
        throw std::invalid_argument("Matrix must be of type float or double");

     if (this->M != this->N)
        throw std::length_error("Matrix is not rectangular");
    
    Matrix<T> copy = this->copy();
    Matrix<T> inverse = Matrix<T>::identity(this->M);

    for (int i = 0; i < this->M; i++) {
        int pivot = i;
        for (int j = i + 1; j < this->M; j++) {
            if (std::abs(copy.matrix[j][i]) > std::abs(copy.matrix[pivot][i])) {
                pivot = j;
            }
        }

        if (std::abs(copy.matrix[pivot][i]) == 0) {
            throw std::invalid_argument("Matrix is singular");
        }

        if (pivot != i) {
            copy.swapRows(i, pivot);
            inverse.swapRows(i, pivot);
        }

        T pivotValue = copy.matrix[i][i];
        for (int j = 0; j < this->N; j++) {
            copy.matrix[i][j] /= pivotValue;
            inverse.matrix[i][j] /= pivotValue;
        }

        for (int j = 0; j < this->M; j++) {
            if (j != i) {
                T factor = copy.matrix[j][i];
                for (int k = 0; k < this->N; k++) {
                    copy.matrix[j][k] -= factor * copy.matrix[i][k];
                    inverse.matrix[j][k] -= factor * inverse.matrix[i][k];
                }
            }
        }
    }

    for (int i = this->M - 1; i >= 0; i--) {
        for (int j = i + 1; j < this->M; j++) {
            T factor = copy.matrix[i][j];
            for (int k = 0; k < this->N; k++) {
                copy.matrix[i][k] -= factor * copy.matrix[j][k];
                inverse.matrix[i][k] -= factor * inverse.matrix[j][k];
            }
        }
    }

    return inverse;   
    }

    T trace() {
        if(this->M != this->N){
            throw std::length_error("Matrix is not rectangular");
        }
        T sum = 0.0;
        for (int i=0; i<this->M; i++){
            sum += matrix[i][i];
        }
        return sum;
    }

    T determinant() {
        if (typeid(T) != typeid(float) && typeid(T) != typeid(double))
            throw std::invalid_argument("Matrix must be of type float or double");

        if (this->M != this->N)
            throw std::length_error("Matrix is not rectangular");
        T totCoeff = 1.0;
        Matrix<T> copy = this->copy();
        //Find pivot row
        for(int i=0; i<this->M; i++){
            int pivot = -1;
            for(int j=i; j<this->M; j++){
                if (copy.matrix[j][i] != 0){
                    pivot = j;
                    break;
                }
            }
            if(pivot == -1){
                //if not pivot then it is singular det=0;
                return totCoeff;
            }
            if(pivot != i){
                copy.swapRows(i, pivot);
                totCoeff *= -1;
            }
            T coeff = copy.matrix[i][i];
            totCoeff *= coeff;
            for(int j=i; j<this->N; j++){
                copy.matrix[i][j] /= coeff;
            }
            for(int j=i+1; j<this->M; j++){
                T factor = copy.matrix[j][i];
                for(int k=i; k<this->N; k++){
                    copy.matrix[j][k] -= (factor*copy.matrix[i][k]);
                }
                
            }
        }   
        return totCoeff;
    }



    Matrix transpose() {
        Matrix<T> copy = this->copy();
        for (int i=0; i<this->M; i++){
            for (int j=0; j<this->N; j++){
                copy.matrix[i][j] = this->matrix[j][i];
            }
        }
        return copy;
    }

    Matrix add(Matrix m) {
        Matrix<T> copy = this->copy();
        if (m.M != this->M || m.N != this->N) {
            throw std::invalid_argument("Invalid Matrix. Provide rectangular matrix.");
        }
        for(int i = 0; i < this->M; i++){
            for(int j = 0; j < this->N; j++){
                copy.matrix[i][j] += m.matrix[i][j];
            }
        }
        return copy;
    }

    static Matrix add(Matrix m1, Matrix m2){
        return m1.add(m2);
    }

    Matrix subtract(Matrix m) {
        Matrix<T> copy = this->copy();
        if (m.M != this->M || m.N != this->N) {
            throw std::invalid_argument("Invalid Matrix. Provide rectangular matrix.");
        }
        for (int i = 0; i < this->M; i++){
            for (int j = 0; j < this->N; j++){
                copy.matrix[i][j] -= m.matrix[i][j];
            }
        }
        return copy;
    }

    static Matrix subtract(Matrix m1, Matrix m2){
        return m1.subtract(m2);
    }

    Matrix neg() {
        Matrix<T> copy = this->copy();
        for (int i=0; i<this->M;i++){
            for (int j=0; j<this->N; j++){
                copy.matrix[i][j] *= -1;
            }
        }
        return copy;
    }

    Matrix multiply(Matrix m){
        if (this->N != m.M)
            throw std::invalid_argument("Matrix must be of compatible dimensions");
        
        Matrix<T> result = Matrix<T>(this->M, m.N);
        for (int i=0; i<this->M; i++){
            for (int j=0; j<m.N; j++){
                for (int k=0; k<this->N; k++){
                    result.matrix[i][j]  += this->matrix[i][k] * m.matrix[k][j];
                }
            }
        }
        return result;
    }

    static Matrix multiply(Matrix m1, Matrix m2){
        return m1.multiply(m2);
    }

    Matrix dot(Matrix m){
        return this->multiply(m.transpose());
    }

    static Matrix dot(Matrix m1, Matrix m2){
        return m1.dot(m2);
    }

    Matrix dot(T scalar){
        Matrix<T> copy = this->copy();
        for (int i=0; i<this->M; i++){
            for (int j=0; j<this->N; j++){
                copy.matrix[i][j] *= scalar;
            }
        }
        return copy;
    }
   
   static Matrix<T> dot(T scalar, Matrix m){
        return m.dot(scalar);
    }

    T magnitude(){
        if(typeid(T) != typeid(float) && typeid(T) != typeid(double)){
            throw std::invalid_argument("Magnitude can only be calculated for float or double matrices");
        }
        T sum = 0.0;
        for (int i=0; i<this->M; i++){
            for (int j=0; j<this->N; j++){
                sum += this->matrix[i][j] * this->matrix[i][j];
            }
        }
        return sqrt(sum);
    }

    Matrix<T> copy() {
        Matrix<T> copy(this->M, this->N);
        for (int i=0; i<this->M; i++){
            for (int j=0; j<this->N; j++){
                copy.matrix[i][j] = this->matrix[i][j];
            }
        }
        return copy;
    }
    
    void print(std::ostream& os) const {
        for (int i=0; i<this->M; i++){
            for (int j=0; j<this->N; j++){
                os << this->matrix[i][j] << " ";
            }
            os << std::endl;
        }
        os << std::endl;
    }
    void print() const{
        print(std::cout);
    }
    
    Matrix operator+(Matrix const& other)   {  return this->add(other); }
    Matrix operator-(Matrix const& other)   {  return this->subtract(other); }
    Matrix operator-()  {  return this->neg(); }
    Matrix operator*(Matrix const& other) { return this->multiply(other); }

    Matrix operator=(Matrix const& other){
        this->M = other.M;
        this->N = other.N;
        this->matrix = other.matrix;
        return *this;
    }
    
    static Matrix zeroes(int rows, int columns){
        return Matrix<T>(rows, columns);
    }

    static Matrix ones(int rows, int columns){
        return Matrix<T>(rows, columns, 1);
    
    }
    static Matrix identity(int size){
        Matrix<T> m(size, size);
        for (int i=0; i<size; i++){
            m.matrix[i][i] = 1;
        }
        return m;
    }
};

template <typename T>
std::ostream& operator<< (std::ostream& os, const Matrix<T>& m){
    m.print(os);
    return os;
}

#endif