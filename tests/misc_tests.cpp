#include <gtest/gtest.h>
#include "test_helpers.h"
#include <iostream>

using namespace ray_tracer::math;
constexpr double pi = 3.14159265358979323846;

int main() {
const Matrix half_quarter = rotate_x(pi/4);
double det = determinant(half_quarter);

}