#include <ray_tracer/lighting/light.h>
#include <ray_tracer/lighting/material.h>


namespace ray_tracer::lighting {

using img::Color;
using math::dot;
using math::norm;
using math::point;
using math::reflect;
using math::Tuple;


Light::Light(const Tuple &position, const Color &intensity)
    : position(position), intensity(intensity) {}



Color lighting(const Material &m, const Light &light,
                                const Tuple &point, const Tuple &eyev,
                                const Tuple &normalv) {
    Color black{0, 0, 0};
    Color diffuse;
    Color specular;
    const Color effective_color = m.color * light.intensity;
    const Tuple lightv{norm(light.position - point)};
    const Color ambient = effective_color * m.ambient;
    const double light_dot_normal = dot(lightv, normalv);
    if (light_dot_normal < 0) {
        diffuse = black;
        specular = black;
    } else {
        diffuse = effective_color * m.diffuse * light_dot_normal;
        const Tuple reflectv = reflect(-lightv, normalv);
        const double reflect_dot_eye = dot(reflectv, eyev);

        if (reflect_dot_eye < 0) {
            specular = black;
        } else {
            double factor = std::pow(reflect_dot_eye, m.shininess);
            specular = light.intensity * m.specular * factor;
        }
    }
    return ambient + diffuse + specular;
}

}  // namespace ray_tracer::lighting