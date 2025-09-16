#include <ray_tracer/math/matrix.h>
#include <cassert>

namespace ray_tracer::math {

Matrix::Matrix(int r, int c, std::initializer_list<double> values) : rows(r), cols(c) {
    if (values.size() != static_cast<size_t>(r * c)) {
        throw std::invalid_argument("inputted values size does not match matrix size");
    }
    data.assign(values.begin(), values.end());
}

Matrix::Matrix(int r, int c) : rows(r), cols(c), data(static_cast<size_t>(r * c), 0.0) {}

Matrix Matrix::identity(int n) {
    Matrix I(n, n);
    for (int i = 0; i < n; ++i) {
        I(i, i, 1.0);
    }
    return I;
}

Matrix Matrix::transpose() const {
        Matrix t(cols, rows);
        for(int i = 0; i < rows; ++i) {
            for(int j = 0; j < cols; ++j){
                t(j, i, (*this)(i, j));
            }
        }
        return t;
    };

bool operator==(const Matrix& a, const Matrix& b) {
    if (a.cols != b.cols || a.rows != b.rows) {
        std::cout << "dimensions mismatch\n";
        return false;
    }
    if (a.data.size() != b.data.size()) {
        std::cout << "data size mismatch\n";
        return false;
    }
    for (int i = 0; i < a.rows * a.cols; ++i) {
        if (!dbl_eql(a.data[i], b.data[i])) {
            std::cout << "data value mismatch at: " << "(" << ((i) / a.cols) << ", "
                      << ((i % a.cols));
            return false;
        }
    }
    return true;
}

Matrix operator*(const Matrix& a, const Matrix& b) {
    assert(a.cols == b.rows && "Matrices must be of form m x n, n x p");
    Matrix prod(a.rows, b.cols);
    for (int i = 0; i < a.rows; ++i) {
        for (int j = 0; j < b.cols; ++j) {
            double prod_sum = 0;
            for (int k = 0; k < a.cols; ++k) {
                prod_sum += (a(i, k) * b(k, j));
            }
            prod(i, j, prod_sum);
        }
    }
    return prod;
}


Matrix Matrix::submatrix(int r, int c) const {
    Matrix sub(rows - 1, cols - 1);
    int k = 0;
    int l = 0;
    for(int i = 0; i < rows; ++i){
        if(i == r) continue;
        for(int j = 0; j < cols; ++j){
            if(j == c) continue;
            sub(k, l, (*this)(i, j));
            ++l;
        }
        l = 0;
        ++k;
    }
    return sub;
}

double minor(const Matrix &m, int r, int c) {
    return determinant(m.submatrix(r, c));
}

double cofactor(const Matrix &m, int r, int c) {
    double min = minor(m, r, c);
    if ((r + c) % 2 != 0) return -min;
    return min;
}

double determinant(const Matrix &m) {
    assert(m.cols == m.rows && "Matrix is not square");
    if(m.cols == 2) return (m(0,0) * m(1, 1)) - (m(0, 1) * m(1, 0));
    int det = 0;
    for(int i = 0; i < m.cols; ++i){
        det += m(0, i) * cofactor(m, 0, i);
    }
    return det;
}

Matrix inverse(const Matrix &m) {
    double det = determinant(m);
    assert(det != 0 && "Matrix is not invertible");
    Matrix m_inv(m.rows, m.cols);
    for(int i = 0; i < m.rows; ++i){
        for(int j = 0; j < m.cols; ++j){
            double cof = cofactor(m, i, j);
            m_inv(j, i, cof/det);
        }
    }

    return m_inv;
}

}  // namespace ray_tracer::math