#include <gtest/gtest.h>
#include "test_helpers.h"

using namespace::ray_tracer::math;
using namespace::ray_tracer::geometry;

TEST(Ray, equality) {
    const Tuple origin = point(1, 2, 3);
    const Tuple direction = vector(4, 5, 6);
    const Ray ray = Ray(origin, direction);
    tuple_eq(ray.origin, origin);
    tuple_eq(ray.direction, direction);
}

TEST(Ray, position) {
    const Tuple origin = point(2, 3, 4);
    const Tuple direction = vector(1, 0, 0);
    const Ray ray = Ray(origin, direction);
    expect_tuple(ray.position(0), 2, 3, 4, 1);
}

TEST(Ray, intersect_sphere_two_points) {
    Ray ray{point(0, 0, -5), vector(0, 0, 1)};
    Sphere sphere{Sphere()};
    std::vector<Intersection> xs = intersect(sphere, ray);
    EXPECT_EQ(xs.size(), 2);
    EXPECT_EQ(xs[0].sphere.id, 0);
    EXPECT_NEAR(xs[1].t, 6.0, 1e-12);
}

TEST(Ray, intersect_sphere_tangent) {
    Ray ray{point(0, 1, -5), vector(0, 0, 1)};
    Sphere sphere{Sphere()};
    std::vector<Intersection> xs = intersect(sphere, ray);
    EXPECT_EQ(xs.size(), 2);
    EXPECT_EQ(xs[0].sphere.id, 1);
    EXPECT_NEAR(xs[0].t, 5.0, 1e-12);
    EXPECT_NEAR(xs[1].t, 5.0, 1e-12);
}

TEST(Ray, intersect_sphere_miss) {
    Ray ray{point(0, 2, -5), vector(0, 0, 1)};
    Sphere sphere{Sphere()};
    std::vector<Intersection> xs = intersect(sphere, ray);
    EXPECT_EQ(xs.size(), 0);
}

TEST(Ray, intersect_inside_sphere) {
    Ray ray{point(0, 0, 0), vector(0, 0, 1)};
    Sphere sphere{Sphere()};
    std::vector<Intersection> xs = intersect(sphere, ray);
    EXPECT_EQ(xs.size(), 2);
    EXPECT_EQ(xs[0].sphere.id, 3);
    EXPECT_NEAR(xs[0].t, -1.0, 1e-12);
    EXPECT_NEAR(xs[1].t, 1.0, 1e-12);
}

TEST(Ray, intersect_sphere_behind_ray) {
    Ray ray{point(0, 0, 5), vector(0, 0, 1)};
    Sphere sphere{Sphere()};
    std::vector<Intersection> xs = intersect(sphere, ray);
    EXPECT_EQ(xs[0].sphere.id, 4);
    EXPECT_EQ(xs.size(), 2);
    EXPECT_NEAR(xs[0].t, -6.0, 1e-12);
    EXPECT_NEAR(xs[1].t, -4.0, 1e-12);
}