#include <ray_tracer/math/util.h>
#include <cassert>
#include <iostream>
#include <stdexcept>
#include <vector>
#pragma once

namespace ray_tracer::math {
struct Matrix {
    int rows;
    int cols;
    std::vector<double> data;

    Matrix(int r, int c, std::initializer_list<double> values);
    Matrix(int r, int c);
    
    static Matrix identity(int n);
    const double& operator()(int r, int c) const { return data[r * cols + c]; }
    void operator()(int r, int c, double val) { data[r * cols + c] = val; }
    Matrix transpose() const;
    Matrix submatrix(int r, int c) const;
};

bool operator==(const Matrix &a, const Matrix &b);
Matrix operator*(const Matrix &a, const Matrix &b);
double minor(const Matrix &m, int r, int c);
double cofactor(const Matrix &m, int r, int c);
double determinant(const Matrix &m);
Matrix inverse(const Matrix &m);

};  // namespace ray_tracer::math

