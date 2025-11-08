#include <ray_tracer/camera/camera.h>
#include <ray_tracer/img/canvas.h>
#include <ray_tracer/math/ray.h>
#include <ray_tracer/world/world.h>
#include <vector>
#include <iostream>
#include <cassert>

namespace ray_tracer::camera {

using img::Canvas;
using img::Color;
using math::inverse;
using math::norm;
using math::point;
using math::Ray;
using math::Tuple;
using world::color_at;
using world::World;
using math::print_tuple;

constexpr double pi = 3.14159265358979323846;

Camera::Camera(std::size_t hsize_, std::size_t vsize_, double field_of_view_)
    : hsize(hsize_), vsize(vsize_), field_of_view(field_of_view_) {
    assert(field_of_view_ > 0 && field_of_view_ < pi);
}

std::vector<double> camera_params(std::size_t hsize, std::size_t vsize, double field_of_view) {
    const double half_view = std::tan(field_of_view / 2.0);
    const double aspect = static_cast<double>(hsize) / static_cast<double>(vsize);
    const double half_width = aspect >= 1.0 ? half_view : half_view * aspect;
    const double half_height = aspect >= 1.0 ? half_view / aspect : half_view;
    return {half_width, half_height};
}

double Camera::pixel_size() const {
    std::vector<double> params = camera_params(hsize, vsize, field_of_view);
    return (params[0] * 2.0) / static_cast<double>(hsize);
}

math::Ray Camera::ray_for_pixel(const std::size_t x, const std::size_t y) const {
    std::vector<double> params = camera_params(hsize, vsize, field_of_view);
    double xoffset = (x + 0.5) * pixel_size();
    double yoffset = (y + 0.5) * pixel_size();
    double world_x = params[0] - xoffset;
    double world_y = params[1] - yoffset;
    Tuple pixel = inverse(trans) * point(world_x, world_y, -1);
    Tuple origin = inverse(trans) * point(0, 0, 0);
    Tuple direction = norm(pixel - origin);
    return Ray{origin, direction};
}

Canvas render(const Camera &camera, const World &world) {
    Canvas image{camera.hsize, camera.vsize};
    for (std::size_t y = 0; y <= camera.vsize - 1; ++y) {
        for (std::size_t x = 0; x <= camera.hsize - 1; ++x) {
            Ray ray{camera.ray_for_pixel(x, y)};
            Color color{color_at(world, ray)};
            image.write_pixel(x, y, color);
        }
    }
    return image;
}

}  // namespace ray_tracer::camera