#pragma once
#include <ray_tracer/math/matrix.h>
#include <cmath>
#include <cstddef>

namespace ray_tracer::math {
struct Ray;
}

namespace ray_tracer::img {
struct Canvas;
}

namespace ray_tracer::world {
struct World;
}

namespace ray_tracer::camera {

struct Camera {
    std::size_t hsize = 0;
    std::size_t vsize = 0;
    double field_of_view = 0;

    math::Matrix trans = math::Matrix::identity(4);

    Camera(std::size_t hsize_, std::size_t vsize_, double field_of_view_);
    double pixel_size() const;
    math::Ray ray_for_pixel(const std::size_t x, const std::size_t y) const;
};

img::Canvas render(const Camera &camera, const world::World &world) ;

}  // namespace ray_tracer::camera