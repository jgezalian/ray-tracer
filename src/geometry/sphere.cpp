#include <ray_tracer/geometry/sphere.h>

namespace ray_tracer::geometry {

using lighting::Material;
using math::inverse;
using math::norm;
using math::point;
using math::Tuple;

std::size_t Sphere::next_id = 0;
Sphere sphere() { return Sphere(); }

Material sphere_mat{Material()};
const Tuple Sphere::normal_at(const Tuple &world_point) {
    const Tuple object_point(inverse(transform) * world_point);
    const Tuple object_normal(object_point - point(0, 0, 0));
    Tuple world_normal((inverse(transform).transpose()) * object_normal);
    world_normal.w = 0;
    return norm(world_normal);
}

}  // namespace ray_tracer::geometry