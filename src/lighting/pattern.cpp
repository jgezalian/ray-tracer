#include <ray_tracer/geometry/shape.h>
#include <ray_tracer/lighting/pattern.h>

using ray_tracer::img::Color;
using ray_tracer::math::chain_transform;
using ray_tracer::math::Matrix;
using ray_tracer::math::print_tuple;
using ray_tracer::math::Tuple;

namespace ray_tracer::lighting {

void Pattern::add_colors(std::initializer_list<Color> color_list) {
    for (auto color : color_list) {
        colors.push_back(color);
    }
}

Color Stripe_Pattern::pattern_at_object(const geometry::Shape* object,
                                        const math::Tuple& world_point) {
    Matrix pattern_transform = chain_transform({inverse(transform), inverse(object->transform)});
    Tuple pattern_point = pattern_transform * world_point;
    int int_pattern_point = static_cast<int>(std::abs(std::floor(pattern_point.x)));
    return colors[static_cast<std::size_t>(int_pattern_point) % colors.size()];
}

}  // namespace ray_tracer::lighting