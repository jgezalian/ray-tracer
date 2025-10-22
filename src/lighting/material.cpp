#include <ray_tracer/lighting/material.h>

using ray_tracer::img::Color;
namespace ray_tracer::lighting {

Material::Material()
    : color(Color{1.0, 1.0, 1.0}), ambient(0.1), diffuse(0.9), specular(0.9), shininess(200) {}
}  // namespace ray_tracer::lighting
