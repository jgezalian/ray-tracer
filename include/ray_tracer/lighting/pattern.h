#pragma once
#include <ray_tracer/img/color.h>
#include <ray_tracer/math/matrix.h>
#include <ray_tracer/math/transform.h>
#include <ray_tracer/math/tuple.h>

#include <vector>

namespace ray_tracer::geometry {
class Shape;
}

namespace ray_tracer::lighting {

class Pattern {
    protected:
        Pattern() :
            transform(math::Matrix::identity(4)),
            colors{img::Color(0, 0, 0), img::Color(1, 1, 1)} {}
        Pattern(std::initializer_list<img::Color> _colors) :
            transform(math::Matrix::identity(4)), colors(_colors) {}

    public:
        virtual ~Pattern() {}
        virtual Pattern* clone() const = 0;
        math::Matrix transform;
        std::vector<img::Color> colors = {};
        void add_colors(std::initializer_list<img::Color> color_list);
        virtual img::Color pattern_at_object(const geometry::Shape* object,
                                             const math::Tuple& world_point) = 0;
};

struct Stripe_Pattern : public Pattern {
        Stripe_Pattern() : Pattern() {}

        Stripe_Pattern(std::initializer_list<img::Color> _colors) : Pattern(_colors) {}

        img::Color pattern_at_object(const geometry::Shape* object,
                                     const math::Tuple& world_point) override;

        Pattern* clone() const override { return new Stripe_Pattern(*this); }
};

struct Gradient_Pattern : public Pattern {
        Gradient_Pattern() : Pattern() {}
};

}  // namespace ray_tracer::lighting
