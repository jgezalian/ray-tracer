#include <ray_tracer/geometry/sphere.h>

namespace ray_tracer::geometry {

    std::size_t Sphere::next_id = 0;
    Sphere sphere() {
        return Sphere();
    }

}