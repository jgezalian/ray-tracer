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

constexpr double pi = 3.14159265358979323846;

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
using ray_tracer::math::shearing;
using ray_tracer::math::Tuple;
using ray_tracer::math::vector;
using ray_tracer::img::canvas_to_ppm;
using ray_tracer::geometry::hit;
using ray_tracer::lighting::lighting;
using ray_tracer::math::rotate_z;
using ray_tracer::math::rotate_x;



void draw_shaded_circle() {
    
    Tuple ray_origin = point(2, -2, -10);
    double wall_z = 10;
    double wall_size = 10;
    std::size_t canvas_pixels = 500;
    double pixel_size = wall_size/canvas_pixels;
    double half_wall = wall_size/2;
    Canvas canvas{canvas_pixels, canvas_pixels};
    Color red = Color{1.0, 0, 0};
    Sphere* sphere = new Sphere;
    //Matrix trans1 = scaling(2, 0.3, 2);
    //Matrix trans2 = rotate_x(pi/3);
    //Matrix chain = chain_transform({trans1, trans2});
    //sphere->set_transform(chain);
    sphere->material.color = Color{1, 0.2, 1};
    Tuple light_pos = point(0, 0, -10);
    Color light_color{1.0, 1.0, 1.0};
    Light light{light_pos, light_color};

    for(int y = 0; y <= canvas_pixels - 1; ++y) {
        double world_y = half_wall - pixel_size * y;
        for(int x = 0; x <= canvas_pixels - 1; ++x) {
            double world_x = -half_wall + pixel_size * x;
            Tuple position = point(world_x, world_y, wall_z);
            Ray ray{ray_origin, norm(position - ray_origin)};
            std::vector<Intersection> xs = intersect(sphere, ray);
            const Intersection* i = hit(xs);
            if(i != nullptr) {
                Tuple point = ray.position(i->t);
                Tuple normal = sphere->normal_at(point);
                Tuple eyev = -ray.direction;
                Color shade = lighting(sphere->material, light, point, eyev, normal, false);
                canvas.write_pixel(x, y, shade);
            }
        }
    }


    std::string ppm_string = canvas_to_ppm(canvas);
    ray_tracer::img::write_ppm(ppm_string, "circle1");
}

int main() {
    draw_shaded_circle();
    return 0;
}