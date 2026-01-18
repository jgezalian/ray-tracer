#pragma once
#include <ray_tracer/img/color.h>
#include <ray_tracer/lighting/pattern.h>

namespace ray_tracer::lighting {

struct Material{
    img::Color color;
    double ambient;
    double diffuse;
    double specular;
    double shininess;
    Pattern* pattern;
    
    Material();
    Material(const Material& other_material);
    Material& operator=(const Material &other_material);
    ~Material() {delete pattern;}


};


}