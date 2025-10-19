#pragma once
#include <ray_tracer/math/ray.h>
#include <ray_tracer/math/matrix.h>

namespace ray_tracer::geometry {

using ray_tracer::math::Matrix;

struct Sphere {
    std::size_t id;
    static std::size_t next_id;
    Matrix transform;
    Sphere() : id(next_id++), transform(ray_tracer::math::Matrix::identity(4)) {};

    void set_transform(const Matrix &mat) {
        transform = mat;
    }
};

Sphere sphere();
}  // namespace ray_tracer::geometry