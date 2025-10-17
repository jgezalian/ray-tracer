#pragma once
#include <ray_tracer/geometry/sphere.h>
#include <ray_tracer/math/ray.h>

#include <vector>

using ray_tracer::geometry::Sphere;
using ray_tracer::math::Ray;

namespace ray_tracer::geometry {

struct Intersection {
    double t;
    Sphere sphere;

    Intersection(double t, Sphere sphere) : t(t), sphere(sphere) {}
};

std::vector<Intersection> intersect(const Sphere &sphere, const Ray &ray);
std::vector<Intersection> intersections(std::initializer_list<Intersection> inters_list);
const Intersection* hit(const std::vector<Intersection> &inters);
}  // namespace ray_tracer::geometry
