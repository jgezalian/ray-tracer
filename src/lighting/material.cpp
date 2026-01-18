#include <ray_tracer/lighting/material.h>

using ray_tracer::img::Color;
namespace ray_tracer::lighting {

Material::Material() :
    color(Color{1.0, 1.0, 1.0}),
    ambient(0.1),
    diffuse(0.9),
    specular(0.9),
    shininess(200),
    pattern(nullptr) {}

Material::Material(const Material& other_material) :
    color(other_material.color),
    ambient(other_material.ambient),
    diffuse(other_material.diffuse),
    specular(other_material.specular),
    shininess(other_material.shininess),
    pattern(other_material.pattern ? other_material.pattern->clone() : nullptr) {}

Material& Material::operator=(const Material& other_material) {
    if(this == &other_material) return *this;
    color = other_material.color;
    ambient = other_material.ambient;
    diffuse = other_material.diffuse;
    specular = other_material.specular;
    shininess = other_material.shininess;
    delete pattern;
    pattern = (other_material.pattern ? other_material.pattern->clone() : nullptr);
    return *this;
}
}  // namespace ray_tracer::lighting
