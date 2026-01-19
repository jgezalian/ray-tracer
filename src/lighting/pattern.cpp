#include <ray_tracer/geometry/shape.h>
#include <ray_tracer/lighting/pattern.h>

using ray_tracer::img::Color;
using ray_tracer::math::chain_transform;
using ray_tracer::math::Matrix;
using ray_tracer::math::print_tuple;
using ray_tracer::math::Tuple;

using ray_tracer::geometry::Shape;
using ray_tracer::math::Tuple;

namespace ray_tracer::lighting {

void Pattern::add_colors(std::initializer_list<Color> color_list) {
    for (auto color : color_list) {
        colors.push_back(color);
    }
}

Color Stripe_Pattern::pattern_at_object(const geometry::Shape* object, const math::Tuple& world_point) {
    Matrix pattern_transform = chain_transform({inverse(object->transform), inverse(transform)});
    Tuple pattern_point = pattern_transform * world_point;
    int int_pattern_point = static_cast<int>(std::abs(std::floor(pattern_point.x)));
    return colors[static_cast<std::size_t>(int_pattern_point) % colors.size()];
}

Color Gradient_Pattern::pattern_at_object(const Shape* object, const Tuple& world_point) {
    Matrix pattern_transform = chain_transform({inverse(object->transform), inverse(transform)});
    Tuple pattern_point = pattern_transform * world_point;
    double c = (pattern_point.x - std::floor(pattern_point.x));
    return colors[0] + ((colors[1] - colors[0]) * c);
}

Color Checkered_Pattern::pattern_at_object(const Shape* object, const Tuple& world_point) {
    Matrix pattern_transform = chain_transform({inverse(object->transform), inverse(transform)});
    Tuple pattern_point = pattern_transform * world_point;
    int sum = static_cast<int>((std::floor(pattern_point.x)) + (std::floor(pattern_point.z)));
    if (sum % 2 == 0) {
        return colors[0];
    }
    return colors[1];
}

}  // namespace ray_tracer::lighting