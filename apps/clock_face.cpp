#include <ray_tracer/img/canvas.h>
#include <ray_tracer/img/color.h>
#include <ray_tracer/math/tuple.h>
#include <ray_tracer/math/matrix.h>
#include <ray_tracer/math/transform.h>
#include <iostream>

using ray_tracer::img::Canvas;
using ray_tracer::img::Color;
using ray_tracer::math::Tuple;
using ray_tracer::math::Matrix;
using ray_tracer::math::point;
using ray_tracer::math::rotate_z;
using ray_tracer::math::inverse;
using ray_tracer::math::scaling;
using ray_tracer::math::translation;

constexpr double pi = 3.14159265358979323846;

void draw_clock_pixel(Tuple &p, Canvas &canvas) {
    const Matrix rot_30_deg = (rotate_z(pi/6));
    const Matrix translate = translation(canvas.width/2 - 1, canvas.height/2 - 1, 0);
    for(std::size_t i = 0; i < 12; ++i) {
        Tuple t_p = translate * p;
        canvas.write_pixel(std::round(t_p.x), std::round(t_p.y), Color(1.0, 1.0, 1.0));
        p = rot_30_deg * p;
    }
}

int main() {
    Canvas canvas = Canvas(100,100);
    Tuple origin = point(0, 0, 0);
    Tuple p = translation(0, 30, 0) * origin;


    draw_clock_pixel(p, canvas);
    std::string ppm_string = canvas_to_ppm(canvas);
    ray_tracer::img::write_ppm(ppm_string, "clock_face");

    return 0;
}