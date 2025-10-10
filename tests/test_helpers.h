#pragma once
#include <gtest/gtest.h>
#include <ray_tracer/img/color.h>
#include <ray_tracer/math/tuple.h>
#include <ray_tracer/math/matrix.h>
#include <ray_tracer/math/transform.h>
#include <vector>

inline void expect_rgb(const ray_tracer::img::Color& c, const double r, const double g,
                       const double b, const double eps = 1e-12) {
    EXPECT_NEAR(c.r, r, eps);
    EXPECT_NEAR(c.g, g, eps);
    EXPECT_NEAR(c.b, b, eps);
}

inline void expect_tuple(const ray_tracer::math::Tuple& t, const double x, const double y,
                         const double z, const double w, const double eps = 1e-12) {
    EXPECT_NEAR(t.x, x, eps);
    EXPECT_NEAR(t.y, y, eps);
    EXPECT_NEAR(t.z, z, eps);
    EXPECT_NEAR(t.w, w, eps);
}

inline void expect_matrix(const ray_tracer::math::Matrix& m, const std::vector<double>& values,
                          const double eps = 1e-12) {
    EXPECT_EQ(m.rows * m.cols, static_cast<int>(values.size()));
    for (std::size_t i = 0; i < m.rows * m.cols; ++i) {
        EXPECT_NEAR(m.data[i], values[i], eps);
    }
}

inline void expect_matrix_eq(const ray_tracer::math::Matrix& a, const ray_tracer::math::Matrix& b) {
    EXPECT_EQ(a.rows, b.rows);
    EXPECT_EQ(a.cols, b.cols);
    EXPECT_EQ(static_cast<int>(a.data.size()), static_cast<int>(b.data.size()));
    for (std::size_t i = 0; i < a.rows * a.cols; ++i) {
        EXPECT_NEAR(a.data[i], b.data[i], 1e-12);
    }
}
