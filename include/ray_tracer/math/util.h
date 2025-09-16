#pragma once
#include <cmath>

inline bool dbl_eql(const double a, const double b) {
    double eps = 1e-12;
    return std::fabs(a - b) < eps;
}