#include <gtest/gtest.h>
#include "test_helpers.h"

using namespace::ray_tracer::math;
using namespace::ray_tracer::geometry;


TEST(Sphere, set_transform) {
    Sphere sphere{Sphere()};
    const Matrix trans = translation(2, 3, 4);
    sphere.set_transform(trans);
    expect_matrix_eq(sphere.transform, trans);
}

TEST(Sphere, set_transform_scaling) {
    const Ray ray = Ray(point(0, 0, -5), vector(0, 0, 1));
    Sphere sphere{Sphere()};
    sphere.set_transform(scaling(2, 2, 2));
    const std::vector<Intersection> xs = intersect(sphere, ray);
    EXPECT_EQ(xs.size(), 2);
    EXPECT_NEAR(xs[0].t, 3, 1e-12);
    EXPECT_NEAR(xs[1].t, 7, 1e-12);
    
}

TEST(Sphere, set_transform_translation) {
    const Ray ray = Ray(point(0, 0, -5), vector(0, 0, 1));
    Sphere sphere;
    sphere.set_transform(translation(5, 0, 0));
    const std::vector<Intersection> xs = intersect(sphere, ray);
    EXPECT_EQ(xs.size(), 0);
}

