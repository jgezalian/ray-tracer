#include <ray_tracer/demo/cannon.h>
#include <ray_tracer/img/canvas.h>
#include <ray_tracer/img/color.h>
#include <ray_tracer/math/tuple.h>

using ray_tracer::demo::launch;
using ray_tracer::img::Canvas;
using ray_tracer::img::Color;
using ray_tracer::math::point;
using ray_tracer::math::Tuple;
using ray_tracer::math::vector;

namespace ray_tracer::demo {
void plot_projectile() {
    Tuple pos = point(0.0, 0.0, 0.0);
    Tuple vel = vector(5, 8, 0.0);
    Tuple vel_norm = norm(vel) * 5;
    Projectile p = Projectile(pos, vel_norm);

    Tuple grav = Tuple(0.0, -0.1, 0.0, 0.0);
    Tuple wind = Tuple(-0.01, 0.0, 0.0, 0.0);
    Environment e = Environment(grav, wind);

    Canvas canvas = Canvas(500, 500);

    while (p.pos.y >= 0) {
        std::size_t x = static_cast<std::size_t>(std::round(p.pos.x));
        std::size_t y = static_cast<std::size_t>(std::round((canvas.height - 1) - p.pos.y));
        if (x >= 0 && x < canvas.width && y >= 0 && y < canvas.height) {
            canvas.write_pixel(x, y, Color(1.0, 1.0, 1.0));
        }
        p = launch(p, e);
    }

    std::string ppm_string = canvas_to_ppm(canvas);
    ray_tracer::img::write_ppm(ppm_string, "projectile");
}
}  // namespace ray_tracer::demo

int main() { ray_tracer::demo::plot_projectile(); }