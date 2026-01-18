#pragma once
#include <ray_tracer/geometry/shape.h>


namespace ray_tracer::geometry {

struct Plane : public Shape{
    Plane() : Shape() {}
    math::Tuple normal_at(const math::Tuple &world_point) const override;
    std::vector<Intersection> local_intersect(const math::Ray &ray) const override;
};


}  // namespace ray_tracer::geometry