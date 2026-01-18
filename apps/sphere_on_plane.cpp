#include <ray_tracer/camera/camera.h>
#include <ray_tracer/geometry/intersection.h>
#include <ray_tracer/geometry/plane.h>
#include <ray_tracer/geometry/sphere.h>
#include <ray_tracer/img/canvas.h>
#include <ray_tracer/img/color.h>
#include <ray_tracer/lighting/light.h>
#include <ray_tracer/lighting/pattern.h>
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
using namespace ray_tracer::lighting;

void draw_scene() {
    World world{default_world()};
    for (auto* object : world.objects) {
        delete object;
    }
    world.objects.clear();

    // floor
    Plane* floor = new Plane();
    // floor->transform = translation(0, -5, 0);
    //floor->material.color = Color(0.1, 1.0, 0.5);
    floor->material.specular = 0;
    Stripe_Pattern* stripe_pattern_floor = new Stripe_Pattern({Color(1, 0, 1), Color(0, 0, 1), Color(0.1, 0.8, 0.2)});
    //stripe_pattern_floor->transform = scaling(10, 10, 10);
    floor->material.pattern = stripe_pattern_floor;
    world.objects.push_back(floor);

    Plane* back_wall = new Plane();
    back_wall->material.color = Color(1.0, 0.0, 0.0);
    back_wall->material.specular = 0;
    back_wall->transform = chain_transform({scaling(1, 3, 1),rotate_x(pi / 2), translation(0.0, 5, 5.0)});
    world.objects.push_back(back_wall);

    // center sphere
    Sphere* center_sphere = new Sphere();
    center_sphere->material.color = Color(1.0, 0.5, 0.5);
    Stripe_Pattern* stripe_pattern_center_sphere = new Stripe_Pattern();
    //stripe_pattern_center_sphere->transform = scaling(1, 1, 1);
    center_sphere->material.pattern = stripe_pattern_center_sphere;
    center_sphere->transform = chain_transform({translation(0, 1, -1), scaling(3, 3, 3)});
    world.objects.push_back(center_sphere);

    // Sphere* left = new Sphere();
    // left->material.color = Color(0.2, 0.4, 1.0);
    // left->material.diffuse = 0.6;
    // left->material.specular = 0.4;
    // left->transform = chain_transform({scaling(0.33, 1.5, 0.33), translation(-3.0, 1.5, 2.0)});
    // world.objects.push_back(left);

    Camera camera{200, 200, pi / 2};
    camera.trans = view_transform(point(0, 3, -10), point(0, 0, 0), vector(0, 1, 0));
    const Canvas img = render(camera, world);
    std::string ppm_string = canvas_to_ppm(img);
    ray_tracer::img::write_ppm(ppm_string, "plane_sphere");
}

int main() {
    draw_scene();
    return 0;
}
