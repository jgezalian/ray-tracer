#include <gtest/gtest.h>
#include "test_helpers.h"

using namespace::ray_tracer::math;
using namespace::ray_tracer::geometry;
using namespace::ray_tracer::lighting;
using ray_tracer::helpers::Computation;


TEST(Sphere, set_transform) {
    Sphere sphere;
    const Matrix trans = translation(2, 3, 4);
    sphere.set_transform(trans);
    expect_matrix_eq(sphere.transform, trans);
}

TEST(Sphere, set_transform_scaling) {
    const Ray ray = Ray(point(0, 0, -5), vector(0, 0, 1));
    Sphere sphere;
    sphere.set_transform(scaling(2, 2, 2));
    const std::vector<Intersection> xs = intersect(&sphere, ray);
    EXPECT_EQ(xs.size(), 2);
    EXPECT_NEAR(xs[0].t, 3, 1e-12);
    EXPECT_NEAR(xs[1].t, 7, 1e-12);
}

TEST(Sphere, set_transform_translation) {
    const Ray ray = Ray(point(0, 0, -5), vector(0, 0, 1));
    Sphere sphere;
    sphere.set_transform(translation(5, 0, 0));
    const std::vector<Intersection> xs = intersect(&sphere, ray);
    EXPECT_EQ(xs.size(), 0);
}

TEST(Sphere, set_transform_translation1) {
    const Ray ray = Ray(point(-5, 0, 0), vector(1, 0, 0));
    Sphere sphere;
    //sphere.set_transform(translation(3, 0, 0));
    const std::vector<Intersection> xs = intersect(&sphere, ray);
    EXPECT_EQ(xs.size(), 2);
    EXPECT_NEAR(xs[0].t, 4, 1e-12);
    EXPECT_NEAR(xs[1].t, 6, 1e-12);
}

TEST(Sphere, normal_at) {
    Tuple p = point(1, 0, 0);
    Sphere sphere;
    const Tuple n = sphere.normal_at(p);
    expect_tuple(n, 1, 0, 0, 0);
}

TEST(Sphere, normal_at_non_axial) {
    Tuple p = point(std::sqrt(3)/3, std::sqrt(3)/3, std::sqrt(3)/3);
    Sphere sphere;
    const Tuple n = sphere.normal_at(p);
    tuple_eq(n, norm(n));
}

TEST(Sphere, normal_at_transformed) {
    Sphere sphere;
    sphere.set_transform(translation(0, 1, 0));
    const Tuple n = sphere.normal_at(point(0, 1.70711, -0.70711));
    tuple_eq(n, vector(0, 0.70711, -0.70711));
} 

TEST(Sphere, default_material) {
    Sphere sphere;
    color_eq(sphere.material.color, Color{1.0, 1.0, 1.0});
    EXPECT_NEAR(sphere.material.ambient, 0.1, 1e-12);
    EXPECT_NEAR(sphere.material.diffuse, 0.9, 1e-12);
    EXPECT_NEAR(sphere.material.specular, 0.9, 1e-12);
    EXPECT_NEAR(sphere.material.shininess, 200, 1e-12);
}

TEST(Sphere, assign_material) {
    Sphere sphere;
    Material mat{};
    mat.ambient = 1;
    mat.pattern = new Stripe_Pattern;
    sphere.material = mat;
    color_eq(sphere.material.color, Color{1.0, 1.0, 1.0});
    EXPECT_NEAR(sphere.material.ambient, 1, 1e-12);
    EXPECT_NEAR(sphere.material.diffuse, 0.9, 1e-12);
    EXPECT_NEAR(sphere.material.specular, 0.9, 1e-12);
    EXPECT_NEAR(sphere.material.shininess, 200, 1e-12);
}