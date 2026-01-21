#include <gtest/gtest.h>
#include "test_helpers.h"

using namespace::ray_tracer::math;
using namespace::ray_tracer::geometry;
using ray_tracer::helpers::Computation;
using ray_tracer::helpers::prepare_computation;

TEST(Intersection, members) {
    const Sphere sphere;
    const Intersection intersection{3.5, &sphere};
    EXPECT_NEAR(intersection.t, 3.5, 1e-12);
    //EXPECT_EQ(sphere.id, 5);
}

TEST(Intersection, aggregate_inters) {
    const Sphere sphere;
    std::vector<Intersection> xs;
    xs.emplace_back(1, &sphere);
    xs.emplace_back(2, &sphere);
    EXPECT_EQ(xs.size(), 2);
    EXPECT_NEAR(xs[0].t, 1, 1e-12);
    EXPECT_NEAR(xs[1].t, 2, 1e-12);
}

TEST(Intersection, hit_positive_t) {
    const Sphere sphere;
    const Intersection i1{1, &sphere};
    const Intersection i2{2, &sphere};
    std::vector<Intersection> xs;
    xs.emplace_back(i1);
    const Intersection* i = hit(xs);
    intersection_eq(*i, i1);
}

TEST(Intersection, hit_mixed_t) {
    const Sphere sphere;
    const Intersection i1{-1, &sphere};
    const Intersection i2{1, &sphere};
    std::vector<Intersection> xs;
    xs.emplace_back(i2);
    const Intersection* i = hit(xs);
    intersection_eq(*i, i2);
}

TEST(Intersection, hit_negative_t) {
    const Sphere sphere;
    const Intersection i1{-2, &sphere};
    const Intersection i2{-1, &sphere};
    std::vector<Intersection> xs;
    xs.emplace_back(i1);
    xs.emplace_back(i2);
    const Intersection* i = hit(xs);
    assert(i == nullptr);
}

TEST(Intersection, many) {
    const Sphere sphere;
    const Intersection i1{5, &sphere};
    const Intersection i2{7, &sphere};
    const Intersection i3{-3, &sphere};
    const Intersection i4{2, &sphere};
    std::vector<Intersection> xs;
    xs.emplace_back(i1);
    xs.emplace_back(i2);
    xs.emplace_back(i3);
    xs.emplace_back(i4);
    const Intersection* i = hit(xs);
    intersection_eq(*i, i4);

}

TEST(Intersection, precompute) {
    const Ray ray{point(0, 0, -5), vector(0, 0, 1)};
    Sphere sphere;
    const Intersection i{4, &sphere};
    const Computation comps = prepare_computation(i, ray);
    EXPECT_NEAR(comps.t, i.t, 1e-5);
    EXPECT_EQ(comps.shape, i.shape);
    tuple_eq(comps.point, point(0, 0, -1));
    tuple_eq(comps.eyev, vector(0, 0, -1));
    tuple_eq(comps.normalv, vector(0, 0, -1));
}

TEST(Intersection, precompute_hit_inside) {
    const Ray ray{point(0, 0, 0), vector(0, 0, 1)};
    Sphere sphere;
    const Intersection i{1,&sphere};
    const Computation comps = prepare_computation(i, ray);
    tuple_eq(comps.point, point(0, 0, 1));
    tuple_eq(comps.eyev, vector(0, 0, -1));
}

TEST(Intersection, ray_parallel_to_plane) {
    const Ray ray{point(0, 10, 0), vector(0, 0, 1)};
    Plane plane;
    std::vector<Intersection> xs;
    plane.intersect(ray, xs);
    EXPECT_EQ(xs.size(), 0);
}

TEST(Intersection, ray_coplanar_to_plane) {
    const Ray ray{point(0, 0, 0), vector(0, 0, 1)};
    Plane plane;
    std::vector<Intersection> xs;
    plane.intersect(ray, xs);
    EXPECT_EQ(xs.size(), 0);
}

TEST(Intersection, ray_intersect_plane_from_above) {
    const Ray ray{point(0, 1, 0), vector(0, -1, 0)};
    Plane plane;
    std::vector<Intersection> xs;
    plane.intersect(ray, xs);
    EXPECT_EQ(xs.size(), 1);
    EXPECT_NEAR(xs[0].t, 1, 1e-12);
    EXPECT_EQ(xs[0].shape, &plane);
}
TEST(Intersection, ray_intersect_plane_from_below) {
    const Ray ray{point(0, -1, 0), vector(0, 1, 0)};
    Plane plane;
    std::vector<Intersection> xs;
    plane.intersect(ray, xs);
    EXPECT_EQ(xs.size(), 1);
    EXPECT_NEAR(xs[0].t, 1, 1e-12);
    EXPECT_EQ(xs[0].shape, &plane);
}