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
#include <sstream>

constexpr double pi = 3.14159265358979323846;

using namespace ray_tracer::world;
using namespace ray_tracer::camera;
using namespace ray_tracer::img;
using namespace ray_tracer::geometry;
using namespace ray_tracer::math;
using namespace ray_tracer::lighting;

void animate_sphere(int i, double delta, World& world, const Camera& camera) {
    Shape* center_sphere = new Sphere();
    Gradient_Pattern* gradient_pattern_center_sphere = new Gradient_Pattern({Color(0, 1, 0), Color(0, 0, 1.0)});
    gradient_pattern_center_sphere->set_transform(chain_transform({scaling(2, 2, 2), translation(-1, 0, 0)}));
    center_sphere->material.pattern = gradient_pattern_center_sphere;
    center_sphere->set_transform(chain_transform({scaling(3.3, 3.3, 3.3), translation(-10 + delta, 1, -1)}));
    world.add(center_sphere);
    const Canvas img = render(camera, world);
    delete world.objects[1];
    world.objects.pop_back();
    std::string ppm_string = canvas_to_ppm(img);
    std::ostringstream oss;
    oss << "frame_" << std::setw(4) << std::setfill('0') << i;
    std::string name = oss.str();
    ray_tracer::img::write_ppm(ppm_string, name);
}

void animate() {
    World world{default_world()};
    for (auto* object : world.objects) {
        delete object;
    }
    world.objects.clear();
    Light light{point(-5, 8, -10), Color{1, 1, 1}};
    world.light = light;

    // floor
    Plane* floor = new Plane();
    floor->set_transform(translation(0, -5, 0));
    Checkered_Pattern* cp = new Checkered_Pattern;
    cp->set_transform(scaling(4, 1, 4));  // bigger checkers on the plane
    floor->material.pattern = cp;
    world.objects.push_back(floor);

    Camera camera{500, 500, pi / 4};
    camera.set_transform(view_transform(point(0, 7, -15), point(0, 0, 0), vector(0, 1, 0)));

    int frames = 100;
    double distance = 20;
    for (int i = 0; i <= frames; ++i) {
        double delta = i * (distance / frames);
        animate_sphere(i, delta, world, camera);
    }
}

int main() {
    animate();
    return 0;
}
