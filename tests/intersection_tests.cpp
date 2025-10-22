#include <gtest/gtest.h>
#include "test_helpers.h"

using namespace::ray_tracer::math;
using namespace::ray_tracer::geometry;

TEST(Intersection, members) {
    const Sphere sphere;
    const Intersection intersection{3.5, sphere};
    EXPECT_NEAR(intersection.t, 3.5, 1e-12);
    EXPECT_EQ(sphere.id, 5);
}

TEST(Intersection, aggregate_inters) {
    const Sphere sphere;
    const Intersection i1{1, sphere};
    const Intersection i2{2, sphere};
    const std::vector<Intersection> xs = intersections({i1, i2});
    EXPECT_EQ(xs.size(), 2);
    EXPECT_NEAR(xs[0].t, 1, 1e-12);
    EXPECT_NEAR(xs[1].t, 2, 1e-12);
}

TEST(Intersection, hit_positive_t) {
    const Sphere sphere;
    const Intersection i1{1, sphere};
    const Intersection i2{2, sphere};
    const std::vector<Intersection> xs = intersections({i1, i2});
    const Intersection* i = hit(xs);
    intersection_eq(*i, i1);
}

TEST(Intersection, hit_mixed_t) {
    const Sphere sphere;
    const Intersection i1{-1, sphere};
    const Intersection i2{1, sphere};
    const std::vector<Intersection> xs = intersections({i1, i2});
    const Intersection* i = hit(xs);
    intersection_eq(*i, i2);
}

TEST(Intersection, hit_negative_t) {
    const Sphere sphere;
    const Intersection i1{-2, sphere};
    const Intersection i2{-1, sphere};
    const std::vector<Intersection> xs = intersections({i1, i2});
    const Intersection* i = hit(xs);
    assert(i == nullptr);
}

TEST(Intersection, many) {
    const Sphere sphere;
    const Intersection i1{5, sphere};
    const Intersection i2{7, sphere};
    const Intersection i3{-3, sphere};
    const Intersection i4{2, sphere};
    const std::vector<Intersection> xs = intersections({i1, i2, i3, i4});
    const Intersection* i = hit(xs);
    intersection_eq(*i, i4);

}

