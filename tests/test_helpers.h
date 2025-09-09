#pragma once
#include <gtest/gtest.h>
#include <ray_tracer/img/color.h>
#include <ray_tracer/math/tuple.h>

inline void expect_rgb(const ray_tracer::img::Color& c, const double r, const double g, const double b, const double eps=1e-12) {
    EXPECT_NEAR(c.r, r, eps);
    EXPECT_NEAR(c.g, g, eps);
    EXPECT_NEAR(c.b, b, eps);
}

inline void expect_tuple(const ray_tracer::math::Tuple &t, const double x, const double y, const double z, const double w, const double eps=1e-12) {
    EXPECT_NEAR(t.x, x, eps);
    EXPECT_NEAR(t.y, y, eps);
    EXPECT_NEAR(t.z, z, eps);
    EXPECT_NEAR(t.w, w, eps);
}