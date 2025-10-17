#pragma once
#include <ray_tracer/math/ray.h>

namespace ray_tracer::geometry {

struct Sphere {
    std::size_t id;
    static std::size_t next_id;
    Sphere() : id(next_id++) {};
};

Sphere sphere();
}  // namespace ray_tracer::geometry