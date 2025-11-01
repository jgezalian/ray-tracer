#pragma once
#include <ray_tracer/math/matrix.h>
#include <ray_tracer/math/ray.h>
#include <ray_tracer/lighting/material.h>

namespace ray_tracer::geometry {

class Shape {
    protected:
        Shape() : id(next_id++), transform(math::Matrix::identity(4)) {};
    public:
        virtual ~Shape() {}
        std::size_t id;
        static inline std::size_t next_id = 0;
        math::Matrix transform;
        lighting::Material material;

        virtual math::Tuple normal_at(const math::Tuple &world_point) const = 0;
        void set_transform(const math::Matrix &mat) { transform = mat; }
};


}  // namespace ray_tracer::geometry