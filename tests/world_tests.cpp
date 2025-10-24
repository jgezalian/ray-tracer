#include <gtest/gtest.h>
#include "test_helpers.h"

using namespace ray_tracer::world;
using ray_tracer::lighting::Light;
using ray_tracer::math::point;
using ray_tracer::img::Color;
using ray_tracer::math::scaling;
using ray_tracer::world::default_world;
using ray_tracer::math::Ray;
using ray_tracer::math::vector;


TEST(world, constructor) {
    World world{};
    EXPECT_FALSE(world.has_light);
    EXPECT_EQ(0, world.objects.size());
}

TEST(world, default) {
    const Light light{point(-10, 10, -10), Color{1, 1, 1}};
    World world{default_world()};
    light_eq(world.light, light);
    color_eq(world.objects[0].material.color, Color{0.8, 1.0, 0.6});
    EXPECT_NEAR(world.objects[0].material.diffuse, 0.7, 1e-12);
    EXPECT_NEAR(world.objects[0].material.specular, 0.2, 1e-12);
    expect_matrix_eq(world.objects[1].transform, scaling(0.5, 0.5, 0.5));
}

TEST(world, intersect_world) {
    World world{default_world()};
    Ray ray{point(0, 0, -5), vector(0, 0, 1)};
    std::vector<Intersection> xs = intersect_world(world, ray);
}