#include <ray_tracer/math/transform.h>
#include <ray_tracer/world/world.h>
#include <ray_tracer/geometry/sphere.h>

namespace ray_tracer::world {

using geometry::Sphere;
using img::Color;
using lighting::Light;
using math::point;
using math::scaling;
using math::Ray;
using geometry::Intersection;
using geometry::intersect;

World::~World() {
    for(auto* object : objects) {
        delete object;
    }
}

World default_world() {
    World world{};
    Light light{point(-10, 10, -10), Color{1, 1, 1}};
    world.has_light = true;
    Sphere* s1 = new Sphere();
    s1->material.color = Color{0.8, 1.0, 0.6};
    s1->material.diffuse = 0.7;
    s1->material.specular = 0.2;
    Sphere* s2 = new Sphere();
    s2->set_transform(scaling(0.5, 0.5, 0.5));

    world.add(s1);
    world.add(s2);
    world.light = light;

    return world;
}

std::vector<ray_tracer::geometry::Intersection> intersect_world(const World &world, const Ray &ray) {
    std::vector<Intersection> xs;
    if(world.objects.size() == 0) return {};
    for(const auto* object : world.objects) {
        auto inters = intersect(object, ray);
        for(auto inter : inters) {
            xs.push_back(inter);
        }
    }
    std::sort(xs.begin(), xs.end(), [](const Intersection &i1, const Intersection &i2) {return i1.t < i2.t;} );
    return xs;
}

}  // namespace ray_tracer::world