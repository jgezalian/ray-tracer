#include <ray_tracer/demo/cannon.h>
#include <ray_tracer/img/canvas.h>
#include <ray_tracer/img/color.h>
#include <ray_tracer/math/tuple.h>

using ray_tracer::img::Canvas; 
using ray_tracer::img::Color;
using ray_tracer::math::Tuple;

int main() {
    Tuple pos = Tuple(0.0, 0.0, 0.0, 1.0);
    Tuple vel = Tuple(5, 8, 0.0, 0.0);
    Tuple vel_norm = norm(vel) * 5;
    Projectile p = Projectile(pos, vel);

    Tuple grav = Tuple(0.0, -0.1, 0.0, 0.0);
    Tuple wind = Tuple(-0.01, 0.0, 0.0, 0.0);
    Environment e = Environment(grav, wind);

    Canvas canvas = Canvas(1000, 1000);

    while (p.pos.y >= 0) {
        canvas.write_pixel(p.pos.x, (canvas.height - 1) - p.pos.y,  Color(1.0, 1.0, 1.0));
        p = launch(p, e);
    }

    std::string ppm_string = canvas_to_ppm(canvas);
    ray_tracer::img::write_ppm(ppm_string);

    return 0;
}
