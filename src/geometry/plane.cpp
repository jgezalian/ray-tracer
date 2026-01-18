#include <ray_tracer/geometry/plane.h>

namespace ray_tracer::geometry {

using lighting::Material;
using math::inverse;
using math::norm;
using math::point;
using math::Tuple;
using math::vector;
using math::Ray;
using math::transform_ray;

constexpr double eps = 1e-5;

Tuple Plane::normal_at(const Tuple& /*world_point*/) const {
    const Tuple object_normal = vector(0, 1, 0); // constant in object space
    Tuple world_normal = inverse(transform).transpose() * object_normal;
    world_normal.w = 0;
    return norm(world_normal);
}

std::vector<Intersection> Plane::local_intersect(const math::Ray &ray) const {
    if(std::abs(ray.direction.y) < eps) {
        return {};
    }
    return {Intersection(-(ray.origin.y/ray.direction.y), this)};
    
}

}  // namespace ray_tracer::geometry