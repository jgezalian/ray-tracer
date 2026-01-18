#include <ray_tracer/geometry/sphere.h>

namespace ray_tracer::geometry {

using lighting::Material;
using math::inverse;
using math::norm;
using math::point;
using math::Tuple;
using math::Ray;

Tuple Sphere::normal_at(const Tuple &world_point) const {
    const Tuple object_point(inverse(transform) * world_point);
    const Tuple object_normal(object_point - point(0, 0, 0));
    Tuple world_normal((inverse(transform).transpose()) * object_normal);
    world_normal.w = 0;
    return norm(world_normal);
}

std::vector<Intersection> Sphere::local_intersect(const math::Ray &ray) const {
    Tuple shape_to_ray{ray.origin - point(0, 0, 0)};
    double a = dot(ray.direction, ray.direction);
    double b = 2 * dot(ray.direction, shape_to_ray);
    double c = dot(shape_to_ray, shape_to_ray) - 1;
    double discriminant = std::pow(b, 2) - (4 * a * c);
    if (discriminant < 0) return {};
    double t1 = (-1 * b - std::sqrt(discriminant)) / (2 * a);
    double t2 = (-1 * b + std::sqrt(discriminant)) / (2 * a);

    const Intersection i1 = Intersection(t1, this);
    const Intersection i2 = Intersection(t2, this);

    return intersections({i1, i2});
}

}  // namespace ray_tracer::geometry