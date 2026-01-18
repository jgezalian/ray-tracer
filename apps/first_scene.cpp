#include <ray_tracer/camera/camera.h>
#include <ray_tracer/geometry/intersection.h>
#include <ray_tracer/geometry/sphere.h>
#include <ray_tracer/img/canvas.h>
#include <ray_tracer/img/color.h>
#include <ray_tracer/lighting/light.h>
#include <ray_tracer/math/matrix.h>
#include <ray_tracer/math/ray.h>
#include <ray_tracer/math/transform.h>
#include <ray_tracer/math/tuple.h>
#include <ray_tracer/world/world.h>
#include <string.h>

#include <iostream>
#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif

constexpr double pi = 3.14159265358979323846;

using namespace ray_tracer::world;
using namespace ray_tracer::camera;
using namespace ray_tracer::img;
using namespace ray_tracer::geometry;
using namespace ray_tracer::math;

void draw_scene() {
    World world{default_world()};
    world.objects.clear();

    // floor
    Sphere* floor = new Sphere();
    floor->transform = scaling(10, 0.01, 10);
    floor->material.color = Color(1, 0.9, 0.9);
    floor->material.specular = 0;
    world.objects.push_back(floor);

    // left_wall
    Sphere* left_wall = new Sphere();
    left_wall->transform = chain_transform(
        {scaling(10, 0.01, 10), rotate_x(pi / 2), rotate_y(-pi / 4), translation(0, 0, 5)});
    left_wall->material = floor->material;
    left_wall->material.color = Color(0, 0.5, 0.7);
    world.objects.push_back(left_wall);

    // right_wall
    Sphere* right_wall = new Sphere();
    right_wall->transform = chain_transform(
        {scaling(10, 0.01, 10), rotate_x(pi / 2), rotate_y(pi / 4), translation(0, 0, 5)});
    right_wall->material = floor->material;
    right_wall->material.color = Color(0.2, 0.5, 0.05);
    world.objects.push_back(right_wall);

    // center sphere
    Sphere* center_sphere = new Sphere();
    center_sphere->material.color = Color(1.0, 0.0, 0.0);
    center_sphere->transform = translation(-0.5, 1, 0.5);
    world.objects.push_back(center_sphere);

    Camera camera{3840, 2160, pi / 2};
    camera.trans = view_transform(point(0, 1.5, -5), point(0, 1, 0), vector(0, 1, 0));
    Canvas img = render(camera, world);
    std::string ppm_string = canvas_to_ppm(img);
    ray_tracer::img::write_ppm(ppm_string, "scene1");
}

#ifdef __EMSCRIPTEN__
extern "C" void EMSCRIPTEN_KEEPALIVE first_scene_render_pixels(unsigned char* charPixels,
                                                               std::size_t width,
                                                               std::size_t height) {
    World world{default_world()};
    world.objects.clear();

    // floor
    Sphere* floor = new Sphere();
    floor->transform = scaling(10, 0.01, 10);
    floor->material.color = Color(1, 0.9, 0.9);
    floor->material.specular = 0;
    world.objects.push_back(floor);

    // left_wall
    Sphere* left_wall = new Sphere();
    left_wall->transform = chain_transform(
        {scaling(10, 0.01, 10), rotate_x(pi / 2), rotate_y(-pi / 4), translation(0, 0, 5)});
    left_wall->material = floor->material;
    world.objects.push_back(left_wall);

    // right_wall
    Sphere* right_wall = new Sphere();
    right_wall->transform = chain_transform(
        {scaling(10, 0.01, 10), rotate_x(pi / 2), rotate_y(pi / 4), translation(0, 0, 5)});
    right_wall->material = floor->material;
    world.objects.push_back(right_wall);

    // center sphere
    Sphere* center_sphere = new Sphere();
    center_sphere->material.color = Color(0.0, 1.0, 0.0);
    center_sphere->transform = translation(0, 1, 0);
    world.objects.push_back(center_sphere);

    Camera camera{width, height, pi / 3};
    camera.trans = view_transform(point(0, 1.5, -5), point(0, 1, 0), vector(0, 1, 0));
    Canvas img = render(camera, world);
    int color_i = 0;
    for (auto& color : img.pixels) {
        charPixels[color_i] = std::fmin(255.0f, 255.0f * color.r);
        charPixels[color_i + 1] = std::fmin(255.0f, 255.0f * color.g);
        charPixels[color_i + 2] = std::fmin(255.0f, 255.0f * color.b);
        charPixels[color_i + 3] = 255;
        color_i += 4;
    }
}
#endif

int main() {
    draw_scene();
    return 0;
}
