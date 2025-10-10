#pragma once
#include <ray_tracer/math/matrix.h>

namespace ray_tracer::math {

Matrix translation(double x, double y, double z);
Matrix scaling(double x, double y, double z);
Matrix rotate_x(double r);
Matrix tuple_to_mat(const Tuple &t);

}