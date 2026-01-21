#include <ray_tracer/geometry/sphere.h>
#include <ray_tracer/math/transform.h>
#include <ray_tracer/world/world.h>

namespace ray_tracer::world {

//using geometry::intersect;
using geometry::Intersection;
using geometry::Sphere;
using helpers::Computation;
using helpers::prepare_computation;
using img::Color;
using lighting::Light;
using lighting::lighting;
using math::magnitude;
using math::norm;
using math::point;
using math::Ray;
using math::scaling;
using math::Tuple;

World::~World() {
    for (auto *object : objects) {
        delete object;
    }
}

World default_world() {
    World world{};
    Light light{point(-10, 10, -10), Color{1, 1, 1}};
    world.has_light = true;
    Sphere *s1 = new Sphere();
    s1->material.color = Color{0.8, 1.0, 0.6};
    s1->material.diffuse = 0.7;
    s1->material.specular = 0.2;
    Sphere *s2 = new Sphere();
    s2->set_transform(scaling(0.5, 0.5, 0.5));

    world.add(s1);
    world.add(s2);
    world.light = light;

    return world;
}

std::vector<Intersection> intersect_world(const World &world, const Ray &ray) {
    std::vector<Intersection> xs;
    if (world.objects.size() == 0) return {};
    for (const auto *object : world.objects) {
        object->intersect(ray, xs);
        // auto inters = intersect(object, ray);
        // for (auto inter : inters) {
        //     xs.push_back(inter);
        // }
    }
    std::sort(xs.begin(), xs.end(),
              [](const Intersection &i1, const Intersection &i2) { return i1.t < i2.t; });
    return xs;
}

Color shade_hit(const World &world, const helpers::Computation &comps) {
    bool in_shadow = is_shadowed(comps.over_point, world);
    return lighting(comps.shape, comps.shape->material, world.light, comps.point, comps.eyev, comps.normalv,
                    in_shadow);
}

Color color_at(const World &world, const math::Ray &ray) {
    std::vector<Intersection> xs{intersect_world(world, ray)};
    const Intersection *hit_ = hit(xs);
    if (hit_ == nullptr) {
        return Color(0, 0, 0);
    }
    Computation comps = prepare_computation(*hit_, ray);
    return shade_hit(world, comps);
}

bool is_shadowed(const math::Tuple &point, const world::World &world) {
    const double dist = magnitude(world.light.position - point);
    Ray ray{point, norm(world.light.position - point)};
    std::vector<Intersection> xs{intersect_world(world, ray)};
    const Intersection *hit_ = hit(xs);
    if (hit_ == nullptr || hit_->t > dist) {
        return false;
    }
    return true;
}

}  // namespace ray_tracer::world