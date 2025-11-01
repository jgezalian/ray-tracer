#pragma once
#include <ray_tracer/geometry/shape.h>


namespace ray_tracer::geometry {

struct Sphere : public Shape{
    Sphere() : Shape() {}
    math::Tuple normal_at(const math::Tuple &world_point) const override;
};


}  // namespace ray_tracer::geometry