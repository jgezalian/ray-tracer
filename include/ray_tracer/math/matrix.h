#pragma once
#include <ray_tracer/math/util.h>
#include <cassert>
#include <stdexcept>
#include <vector>
#include <ray_tracer/math/tuple.h>



namespace ray_tracer::math {
struct Matrix {
    std::size_t rows;
    std::size_t cols;
    std::vector<double> data;

    Matrix(std::size_t r, std::size_t c, std::initializer_list<double> values);
    Matrix(std::size_t r, std::size_t c);
    
    static Matrix identity(int n);
    const double& operator()(std::size_t r, std::size_t c) const { return data[(r * cols + c)]; }
    void operator()(std::size_t r, std::size_t c, double val) { data[(r * cols + c)] = val; }
    Matrix transpose() const;
    Matrix submatrix(std::size_t r, std::size_t c) const;
};

bool operator==(const Matrix &a, const Matrix &b);
Matrix operator*(const Matrix &a, const Matrix &b);
Tuple operator*(const Matrix &m, const Tuple &t);
double minor(const Matrix &m, std::size_t r, std::size_t c);
double cofactor(const Matrix &m, std::size_t r, std::size_t c);
double determinant(const Matrix &m);
Matrix inverse(const Matrix &m); 
void print_matrix(const Matrix &m);

};  // namespace ray_tracer::math

