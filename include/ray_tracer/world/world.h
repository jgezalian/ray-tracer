#pragma once
#include <vector>
#include <ray_tracer/geometry/sphere.h>
#include <ray_tracer/lighting/light.h>
#include <ray_tracer/geometry/intersection.h>

namespace ray_tracer::world {

    struct World{   

        std::vector<geometry::Sphere> objects;
        lighting::Light light;  
        bool has_light = false;
        
    };

    World default_world();

    std::vector<geometry::Intersection> intersect_world(const World &world, const math::Ray &ray);

}  // namespace ray_tracer::world
