#include <ray_tracer/geometry/intersection.h>
#include <ray_tracer/geometry/sphere.h>
#include <ray_tracer/img/canvas.h>
#include <ray_tracer/img/color.h>
#include <ray_tracer/lighting/light.h>
#include <ray_tracer/math/matrix.h>
#include <ray_tracer/math/ray.h>
#include <ray_tracer/math/transform.h>
#include <ray_tracer/math/tuple.h>

#include <iostream>

using ray_tracer::geometry::intersect;
using ray_tracer::geometry::Intersection;
using ray_tracer::geometry::Sphere;
using ray_tracer::img::Canvas;
using ray_tracer::img::Color;
using ray_tracer::lighting::Light;
using ray_tracer::math::chain_transform;
using ray_tracer::math::inverse;
using ray_tracer::math::Matrix;
using ray_tracer::math::point;
using ray_tracer::math::Ray;
using ray_tracer::math::scaling;
using ray_tracer::math::translation;
using ray_tracer::math::Tuple;
using ray_tracer::math::vector;
using ray_tracer::math::norm;
using ray_tracer::geometry::hit;

// void draw_circle() {
//     Canvas canvas{1001, 1001};
//     double half_width = (canvas.width - 1) / 2.0;
//     double half_height = (canvas.height - 1) / 2.0;
//     const Matrix translate = translation(half_width, half_height, 0);
//     Sphere* sphere = new Sphere();
//     sphere->material.color = Color{1, 0.2, 1};
//     const Tuple light_pos = point(-10, 10, -10);
//     const Color light_color = Color{1, 1, 1};
//     const Light light{light_pos, light_color};
//     Color red{1.0, 0.0, 0.0};
//     Matrix scale1(scaling(1, 0.5, 1));
//     Matrix scale2(scaling(400, 400, 400));
//     Matrix trans_chain = chain_transform({scale1, scale2});
//     sphere->set_transform(trans_chain);
//     for (int y = -1 * half_height; y <= half_height; ++y) {
//         const Ray ray = Ray(point(-1 * half_width, y, 0), vector(1, 0, 0));
//         const std::vector<Intersection> xs = intersect(sphere, ray);
//         if (xs.size() > 0) {

//             double t_0 = xs[0].t;
//             double t_1 = xs[1].t;
//             double x_0 = ray.position(t_0).x;
//             double x_1 = ray.position(t_1).x;
//             for (int x = static_cast<int>(x_0); x <=static_cast<int>(x_1); ++x) {
//                 const Tuple p = point(x, y, 0);
//                 const Tuple p_trans = translate * p;
//                 canvas.write_pixel((p_trans.x), (p_trans.y), red);
//             }
//         }
//     }

//     std::string ppm_string = canvas_to_ppm(canvas);
//     ray_tracer::img::write_ppm(ppm_string, "circle");
// }

void drawCircle() {
    std::size_t width = 100;
    std::size_t height = 100;
    double wall_z = 5;
    double wall_size = 1;
    double pixel_size = wall_size/width;
    double half = wall_size/2;
    Tuple ray_origin{point(0, 0, -5)};
    Canvas canvas{width, height};
    Sphere s1{};
    

    for (int i = 0; i < height - 1; ++i) {
        double world_y = half - pixel_size * i;
        for (int j = 0; j < width - 1; ++j) {
            double world_x = -half + pixel_size * j;
            Tuple pos = point(world_x, world_y, wall_z);
            Ray ray{ray_origin, norm(pos - ray_origin)};
            std::vector<Intersection> xs = intersect(&s1, ray);
            if(hit(xs) != nullptr) {
                canvas.write_pixel(j, i, Color(1, 0, 0));
            }
        }
    }
    std::string ppm_string = canvas_to_ppm(canvas);
    ray_tracer::img::write_ppm(ppm_string, "circle");
}

int main() {
    // draw_circle();
    drawCircle();
    return 0;
}
