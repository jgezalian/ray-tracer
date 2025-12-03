#include <ray_tracer/math/util.h>
#include <ray_tracer/math/tuple.h>

using ray_tracer::math::Tuple;

namespace ray_tracer::math {

bool dbl_eql(const double a, const double b) {
    double eps = 1e-12;
    return std::fabs(a - b) < eps;
}

double hypot(const Tuple &t) {
    return  std::sqrt(std::pow((t.x), 2) + std::pow((t.y), 2) + std::pow(t.z, 2));
}
}