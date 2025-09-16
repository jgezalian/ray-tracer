#include <gtest/gtest.h>
#include <ray_tracer/math/matrix.h>

#include "test_helpers.h"

using namespace ray_tracer::math;

TEST(Matrix, init) {
    const Matrix m(2, 2, {0.0, 1.0, 2.0, 3.0});
    expect_matrix(m, {0.0, 1.0, 2.0, 3.0});
}

TEST(Matrix, equality) {
    const Matrix a(2, 2, {0.0, 1.0, 2.0, 3.0});
    const Matrix b(2, 2, {0.0, 1.0, 2.0, 3.0});
    EXPECT_TRUE(a == b);
}

TEST(Matrix, multiplication) {
    const Matrix a(3, 3, {1, 2, 3, 3, 2, 1, 1, 2, 3});
    const Matrix b(3, 3, {4, 5, 6, 6, 5, 4, 4, 6, 5});
    expect_matrix(a * b, {28, 33, 29, 28, 31, 31, 28, 33, 29});
}

TEST(Matrix, identity) {
    const Matrix m(2, 2, {0.0, 1.0, 2.0, 3.0});
    const Matrix I = Matrix::identity(2);
    expect_matrix(m * I, {0.0, 1.0, 2.0, 3.0});
}

TEST(Matrix, transpose) {
    const Matrix m(2, 2, {0.0, 1.0, 2.0, 3.0});
    const Matrix t = m.transpose();
    expect_matrix(t, {0.0, 2.0, 1.0, 3.0});
}

TEST(Matrix, transpose_rectangular) {
    const Matrix m(2, 3, {1, 2, 3, 4, 5, 6});
    const Matrix t = m.transpose();
    // expected shape: 3x2, data: {1,4,2,5,3,6}
    expect_matrix(t, {1, 4, 2, 5, 3, 6});
}

TEST(Matrix, submatrix) {
    const Matrix m(4, 4, {-6, 1, 1, 6, -8, 5, 8, 6, -1, 0, 8, 2, -7, 1, -1, 1});
    expect_matrix(m.submatrix(2, 1), {-6, 1, 6, -8, 8, 6, -7, -1, 1});
}