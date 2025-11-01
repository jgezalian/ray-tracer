#pragma once
#include <ray_tracer/geometry/shape.h>

namespace ray_tracer::helpers { 

struct Computation {
    double t = 0;
    const geometry::Shape* shape = nullptr;
    math::Tuple point = math::point(0, 0, 0);
    math::Tuple eyev = math::vector(0, 0, 0);
    math::Tuple normalv = math::vector(0, 0, 0);
    bool inside = false;
};
}