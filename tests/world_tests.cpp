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
using ray_tracer::geometry::Intersection;
using ray_tracer::helpers::Computation;
using ray_tracer::helpers::prepare_computation;
using ray_tracer::world::color_at;
using ray_tracer::geometry::Shape;
using ray_tracer::world::is_shadowed;


TEST(world, constructor) {
    World world{};
    EXPECT_FALSE(world.has_light);
    EXPECT_EQ(0, world.objects.size());
}

TEST(world, default_world) {
    const Light light{point(-10, 10, -10), Color{1, 1, 1}};
    World world{default_world()};
    light_eq(world.light, light);
    color_eq(world.objects[0]->material.color, Color{0.8, 1.0, 0.6});
    EXPECT_NEAR(world.objects[0]->material.diffuse, 0.7, 1e-12);
    EXPECT_NEAR(world.objects[0]->material.specular, 0.2, 1e-12);
    expect_matrix_eq(world.objects[1]->transform, scaling(0.5, 0.5, 0.5));
}

TEST(world, intersect_world) {
    World world{default_world()};
    Ray ray{point(0, 0, -5), vector(0, 0, 1)};
    std::vector<Intersection> xs = intersect_world(world, ray);
    EXPECT_EQ(xs.size(), 4);
    EXPECT_NEAR(xs[0].t, 4, 1e-12);
    EXPECT_NEAR(xs[1].t, 4.5, 1e-12);
    EXPECT_NEAR(xs[2].t, 5.5, 1e-12);
    EXPECT_NEAR(xs[3].t, 6, 1e-12);
}

TEST(world, shade_hit) {
    const World world{default_world()};
    const Ray ray(point(0, 0, -5), vector(0, 0, 1));
    const Intersection i{4, world.objects[0]};
    const Computation comps = prepare_computation(i, ray);
    const Color c = shade_hit(world, comps);
    color_eq(c, Color{0.38066, 0.47583, 0.2855});
}

TEST(world, shade_hit_inside) {
    World world{default_world()};
    world.light = Light(point(0, 0.25, 0), Color(1, 1, 1));
    const Ray ray(point(0, 0, 0), vector(0, 0, 1));
    const Intersection i{0.5, world.objects[1]};
    const Computation comps = prepare_computation(i, ray);
    const Color c = shade_hit(world, comps);
    color_eq(c, Color{0.90498, 0.90498, 0.90498});
}

TEST(world, miss_color) {
    World world{default_world()};
    Ray ray(point(0, 0, -5), vector(0, 1, 0));
    Color c = color_at(world,ray);
    color_eq(c, Color(0, 0, 0));
}

TEST(world, hit_color) {
    World world{default_world()};
    Ray ray(point(0, 0, -5), vector(0, 0, 1));
    Color c = color_at(world,ray);
    color_eq(c, Color(0.38066, 0.47583, 0.2855));
}

TEST(world, behind_ray_color) {
    World world{default_world()};
    Shape* outer = world.objects[0];
    outer->material.ambient = 1;
    Shape* inner = world.objects[1];
    inner->material.ambient = 1;
    Ray ray(point(0, 0, 0.75), vector(0, 0, -1));
    Color c = color_at(world, ray);
    color_eq(c, inner->material.color);
}

TEST(world, no_shadow) {
    World world{default_world()};
    Tuple p{point(0, 10, 0)};
    EXPECT_EQ(is_shadowed(p, world), 0);
}

TEST(world, shadow_between_obj){
    World world{default_world()};
    Tuple p{point(10, -10, 10)};
    EXPECT_EQ(is_shadowed(p, world), 1);
}

TEST(world, no_shadow_behind_light){
    World world{default_world()};
    Tuple p{point(-20, 20, 20)};
    EXPECT_EQ(is_shadowed(p, world), 0);
}

TEST(world, no_shadow_obj_behind_point){
    World world{default_world()};
    Tuple p{point(-2, 2, -2)};
    EXPECT_EQ(is_shadowed(p, world), 0);
}