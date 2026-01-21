#pragma once
#include <vector>
#include <ray_tracer/math/ray.h>
#include <initializer_list>


namespace ray_tracer::geometry {

class Shape;

struct Intersection {
    double t;
    const Shape* shape;

    Intersection(double t_, const Shape* shape_) : t(t_), shape(shape_) {}
};

//std::vector<Intersection> intersect(const Shape* shape, const math::Ray &ray);
//std::vector<Intersection> intersections(std::initializer_list<Intersection> inters_list);
const Intersection* hit(const std::vector<Intersection> &inters);
}  // namespace ray_tracer::geometry
