#include <ray_tracer/geometry/intersection.h>
#include <ray_tracer/geometry/sphere.h>
#include <ray_tracer/math/ray.h>

namespace ray_tracer::geometry {

using math::point;
using math::Tuple;
using math::transform_ray;
using math::inverse;
using math::print_matrix;
using math::Ray;



std::vector<Intersection> intersect(const Shape* shape, const Ray &ray) {
    const Ray t_ray = transform_ray(ray, inverse(shape->transform));
    Tuple shape_to_ray{t_ray.origin - point(0, 0, 0)};
    double a = dot(t_ray.direction, t_ray.direction);
    double b = 2 * dot(t_ray.direction, shape_to_ray);
    double c = dot(shape_to_ray, shape_to_ray) - 1;
    double discriminant = std::pow(b, 2) - (4 * a * c);
    if (discriminant < 0) return {};
    double t1 = (-1 * b - std::sqrt(discriminant)) / (2 * a);
    double t2 = (-1 * b + std::sqrt(discriminant)) / (2 * a);

    const Intersection i1 = Intersection(t1, shape);
    const Intersection i2 = Intersection(t2, shape);
    
    return intersections({i1, i2});
}

std::vector<Intersection> intersections(std::initializer_list<Intersection> inters_list) {
    return std::vector<Intersection>{inters_list};
}

const Intersection* hit(const std::vector<Intersection> &inters) {
    const Intersection* hit = nullptr;
    double min_t = std::numeric_limits<double>::infinity();
    for(auto &inter : inters) {
        if(inter.t >= 0 && inter.t < min_t) {
            min_t = inter.t;
            hit = &inter;
        }

    }
    return hit;
}

}  // namespace ray_tracer::geometry