#pragma once
#include <ray_tracer/math/matrix.h>
#include <ray_tracer/math/ray.h>
#include <ray_tracer/lighting/material.h>

namespace ray_tracer::geometry {

struct Sphere {
    std::size_t id;
    static std::size_t next_id;
    math::Matrix transform;
    Sphere() : id(next_id++), transform(math::Matrix::identity(4)) {};
    const math::Tuple normal_at(const math::Tuple &world_point);
    lighting::Material material;

    void set_transform(const math::Matrix &mat) { transform = mat; }
};

Sphere sphere();
}  // namespace ray_tracer::geometry