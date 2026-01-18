#include <ray_tracer/camera/camera.h>
#include <ray_tracer/geometry/intersection.h>
#include <ray_tracer/geometry/plane.h>
#include <ray_tracer/geometry/sphere.h>
#include <ray_tracer/img/canvas.h>
#include <ray_tracer/img/color.h>
#include <ray_tracer/lighting/light.h>
#include <ray_tracer/math/matrix.h>
#include <ray_tracer/math/ray.h>
#include <ray_tracer/math/transform.h>
#include <ray_tracer/math/tuple.h>
#include <ray_tracer/world/world.h>

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

    // Clean up the default spheres so we can build our own scene
    for (auto* object : world.objects) {
        delete object;
    }
    world.objects.clear();

    // Floor plane
    Plane* floor = new Plane();
    floor->material.color = Color(1.0, 0.9, 0.9);
    floor->material.specular = 0;
    world.objects.push_back(floor);

    // Left wall (tilted plane)
    Plane* left_wall = new Plane();
    left_wall->transform = chain_transform(
        {scaling(5, 0.01, 5), rotate_x(pi / 2), rotate_y(-pi / 4), translation(0, 0, 5)});
    left_wall->material = floor->material;
    left_wall->material.color = Color(0.3, 0.3, 0.7);
    world.objects.push_back(left_wall);

    // Right wall (tilted plane)
    Plane* right_wall = new Plane();
    right_wall->transform = chain_transform(
        {scaling(5, 0.01, 5), rotate_x(pi / 2), rotate_y(pi / 4), translation(0, 0, 5)});
    right_wall->material = floor->material;
    right_wall->material.color = Color(0.3, 0.7, 0.3);
    world.objects.push_back(right_wall);

    // Large red sphere slightly left and forward
    Sphere* middle = new Sphere();
    middle->material.color = Color(1.0, 0.2, 0.2);
    middle->material.diffuse = 0.7;
    middle->material.specular = 0.3;
    middle->transform = chain_transform({translation(-1.8, 1.0, -1.8), scaling(0.75, 0.75, 0.75)});
    world.objects.push_back(middle);

    // Small green sphere to the right
    Sphere* right = new Sphere();
    right->material.color = Color(0.2, 1.0, 0.2);
    right->material.diffuse = 0.7;
    right->material.specular = 0.3;
    right->transform = chain_transform({scaling(0.5, 0.5, 0.5), translation(1.5, 0.5, -0.5)});
    world.objects.push_back(right);

    // Tall blue-ish “pillar” in the back-left
    Sphere* left = new Sphere();
    left->material.color = Color(0.2, 0.4, 1.0);
    left->material.diffuse = 0.6;
    left->material.specular = 0.4;
    left->transform =
        chain_transform({scaling(0.33, 1.5, 0.33), translation(0, 1.6, -2.2), rotate_x(pi/5), rotate_y(-pi/6)});
    world.objects.push_back(left);

    // Camera looking slightly down at the scene
    Camera camera{1000, 1000, pi / 2.2};
    camera.trans = view_transform(point(0, 1.5, -6), point(0, 1, 0), vector(0, 1, 0));

    Canvas img = render(camera, world);
    std::string ppm_string = canvas_to_ppm(img);
    ray_tracer::img::write_ppm(ppm_string, "demo_scene");
}

int main() {
    draw_scene();
    return 0;
}
