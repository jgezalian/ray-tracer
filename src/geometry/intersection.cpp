#include <ray_tracer/geometry/intersection.h>
//#include <ray_tracer/geometry/sphere.h>
#include <ray_tracer/geometry/shape.h>
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
    return shape->local_intersect(t_ray);
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