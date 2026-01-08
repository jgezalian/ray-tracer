#include <gtest/gtest.h>
#include "test_helpers.h"
#include <iostream>

using namespace ray_tracer::camera;
using ray_tracer::math::Matrix;
using ray_tracer::camera::Camera;
using ray_tracer::math::Ray;
using ray_tracer::math::point;
using ray_tracer::math::translation;
using ray_tracer::math::rotate_y;
using ray_tracer::math::vector;
using ray_tracer::world::World;
using ray_tracer::world::default_world;
using ray_tracer::math::view_transform;
using ray_tracer::img::Canvas;
using ray_tracer::img::Color;

constexpr double pi = 3.14159265358979323846;

TEST(camera, construct) {
    Camera camera{160, 120, pi/2};
    EXPECT_NEAR(camera.hsize, 160, 1e-12);
    EXPECT_NEAR(camera.vsize, 120, 1e-12);
    EXPECT_NEAR(camera.field_of_view, pi/2, 1e-12);
    expect_matrix_eq(camera.trans, Matrix::Matrix::identity(4));
}

TEST(camera, pixel_size_horizontal) {
    Camera camera{200, 125, pi/2};
    EXPECT_NEAR(camera.pixel_size, 0.01, 1e-12);
}

TEST(camera, pixel_size_vertical) {
    Camera camera{125, 200, pi/2};
    EXPECT_NEAR(camera.pixel_size, 0.01, 1e-12);
}

TEST(camera, ray_through_center) {
    Camera camera{201, 101, pi/2};
    Ray ray{camera.ray_for_pixel(100, 50)};
    tuple_eq(ray.origin, point(0, 0, 0));
    tuple_eq(ray.direction, vector(0, 0, -1));
}

TEST(camera, ray_through_corner) {
    Camera camera{201, 101, pi/2};
    Ray ray{camera.ray_for_pixel(0, 0)};
    tuple_eq(ray.origin, point(0, 0, 0));
    tuple_eq(ray.direction, vector(0.66519, 0.33259, -0.66851));
}

TEST(camera, ray_camera_transformed) {
    Camera camera{201, 101, pi/2};
    Ray ray{camera.ray_for_pixel(0, 0)};
    camera.trans = rotate_y(pi/4) * translation(0, -2, 5);
    tuple_eq(ray.origin, point(0, 0, 0));
    tuple_eq(ray.direction, vector(0.66519, 0.33259, -0.66851));
}

TEST(camera, render) {
    World world{default_world()};
    Camera camera{11, 11, pi/2};
    Tuple from{point(0, 0, -5)};
    Tuple to{point(0, 0, 0)};
    Tuple up{vector(0, 1, 0)};
    camera.trans = view_transform(from, to, up);
    Canvas img = render(camera, world);
    color_eq(img.pixel_at(5, 5), Color(0.38066, 0.47583, 0.2855));
}