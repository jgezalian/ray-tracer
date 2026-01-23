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
        double aspect = 0;
        double half_view = 0;
        double half_width = 0;
        double half_height = 0;
        double pixel_size = 0;

        Camera(std::size_t hsize_, std::size_t vsize_, double field_of_view_);

        math::Ray ray_for_pixel(const std::size_t x, const std::size_t y) const;

        void set_transform(const math::Matrix &trans_) {
            trans = trans_;
            inverse_trans = math::inverse_gauss_jordan(trans_);
        }

        const math::Matrix& get_transform() const {
            return trans;
        }

        const math::Matrix& get_inverse_transform() const {
            return inverse_trans;
        }

        private:
            math::Matrix trans = math::identity(4);
            math::Matrix inverse_trans = math::inverse_gauss_jordan(trans);


};

img::Canvas render(const Camera &camera, const world::World &world);

}  // namespace ray_tracer::camera