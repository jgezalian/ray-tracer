#include <ray_tracer/math/matrix.h>
#include <ray_tracer/math/tuple.h>
#include <iostream>
#include <cassert>

namespace ray_tracer::math {

Matrix::Matrix(std::size_t r, std::size_t c, std::initializer_list<double> values) : rows(r), cols(c) {
    assert(r >= 0 && c >= 0 && "negative input size");
    if (values.size() != (r * c)) {
        throw std::invalid_argument("inputted values size does not match matrix size");
    }
    data.assign(values.begin(), values.end());
}

Matrix::Matrix(std::size_t r, std::size_t c) : rows(r), cols(c), data((r * c), 0.0) {}

Matrix identity(std::size_t n) {
    Matrix I(n, n);
    for (std::size_t i = 0; i < n; ++i) {
        I(i, i, 1.0);
    }
    return I;
}

Matrix Matrix::transpose() const {
    Matrix t(cols, rows);
    for (std::size_t i = 0; i < rows; ++i) {
        for (std::size_t j = 0; j < cols; ++j) {
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
    for (std::size_t i = 0; i < a.rows * a.cols; ++i) {
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
    for (std::size_t i = 0; i < a.rows; ++i) {
        for (std::size_t j = 0; j < b.cols; ++j) {
            double prod_sum = 0;
            for (std::size_t k = 0; k < a.cols; ++k) {
                prod_sum += (a(i, k) * b(k, j));
            }
            prod(i, j, prod_sum);
        }
    }
    return prod;
}

Matrix Matrix::submatrix(std::size_t r, std::size_t c) const {
    Matrix sub(rows - 1, cols - 1);
    std::size_t k = 0;
    std::size_t l = 0;
    for (std::size_t i = 0; i < rows; ++i) {
        if (i == r) continue;
        for (std::size_t j = 0; j < cols; ++j) {
            if (j == c) continue;
            sub(k, l, (*this)(i, j));
            ++l;
        }
        l = 0;
        ++k;
    }
    return sub;
}

double minor(const Matrix& m, std::size_t r, std::size_t c) { return determinant(m.submatrix(r, c)); }

double cofactor(const Matrix& m, std::size_t r, std::size_t c) {
    double min = minor(m, r, c);
    if ((r + c) % 2 != 0) return -min;
    return min;
}

double determinant(const Matrix& m) {
    assert(m.cols == m.rows && "Matrix is not square");
    if (m.cols == 2) {
        return (m(0, 0) * m(1, 1)) - (m(0, 1) * m(1, 0));
    };
    double det = 0;
    for (std::size_t i = 0; i < m.cols; ++i) {
        det += m(0, i) * cofactor(m, 0, i);
    }
    return det;
}

Matrix inverse(const Matrix& m) {
    double det = determinant(m);
    assert(det != 0 && "Matrix is not invertible");
    Matrix m_inv(m.rows, m.cols);
    for (std::size_t i = 0; i < m.rows; ++i) {
        for (std::size_t j = 0; j < m.cols; ++j) {
            double cof = cofactor(m, i, j);
            m_inv(j, i, cof / det);
        }
    }

    return m_inv;
}

Matrix inverse_gauss_jordan(const Matrix &m) {
    Matrix inverse = m;
    Matrix I = identity(m.cols);
    
    return inverse;

}

Tuple operator*(const Matrix& m, const Tuple& t) {
    const Matrix t_mat = Matrix(4, 1, {t.x, t.y, t.z, t.w});
    Matrix prod = m * t_mat;
    const Tuple t_prod = Tuple(prod.data[0], prod.data[1], prod.data[2], prod.data[3]);
    return t_prod;
}

void print_matrix(const Matrix &m) {
    for(std::size_t i = 0; i < m.rows; ++i) {
        for(std::size_t j = 0; j < m.cols; ++j) {
            std::cout << m(i, j) << " ";
        }
        std::cout << '\n';
    }
    std::cout << '\n';
}

}  // namespace ray_tracer::math