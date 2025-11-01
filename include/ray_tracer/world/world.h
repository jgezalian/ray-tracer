#pragma once
#include <vector>
#include <ray_tracer/geometry/shape.h>
#include <ray_tracer/lighting/light.h>
#include <ray_tracer/geometry/intersection.h>

namespace ray_tracer::world {

    struct World{   
        World() = default;
        ~World();

        void add(geometry::Shape* shape) {
            objects.push_back(shape);
        }
        std::vector<geometry::Shape*> objects;
        lighting::Light light;  
        bool has_light = false;
        
    };

    World default_world();

    std::vector<geometry::Intersection> intersect_world(const World &world, const math::Ray &ray);

}  // namespace ray_tracer::world
