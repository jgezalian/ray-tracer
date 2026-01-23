#pragma once
#include <ray_tracer/geometry/intersection.h>
#include <ray_tracer/lighting/material.h>
#include <ray_tracer/math/matrix.h>
#include <ray_tracer/math/ray.h>

namespace ray_tracer::geometry {

struct Intersection;

class Shape {
    protected:
        Shape() : id(next_id++), transform(math::identity(4)) {};
        virtual void local_intersect(const math::Ray &ray, std::vector<Intersection> &world_intersections) const = 0;
        //friend std::vector<Intersection> intersect(const Shape *shape, const math::Ray &ray);

    public:
        virtual void intersect(const math::Ray& ray, std::vector<Intersection>& world_intersections) const{
            math::Ray t_ray = math::transform_ray(ray, get_inverse_transform());
            local_intersect(t_ray, world_intersections);
        }
        math::Matrix get_transform() const { return transform; };
        math::Matrix get_inverse_transform() const { return inverse_transform; };
        virtual ~Shape() {}
        std::size_t id;
        static inline std::size_t next_id = 0;
        lighting::Material material;
        virtual math::Tuple normal_at(const math::Tuple &world_point) const = 0;
        void set_transform(const math::Matrix &mat) { transform = mat; inverse_transform = math::inverse_gauss_jordan(mat); }

    private:
        math::Matrix transform = math::identity(4);
        math::Matrix inverse_transform = math::inverse_gauss_jordan(transform);
};

}  // namespace ray_tracer::geometry