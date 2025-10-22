#pragma once
#include <ray_tracer/img/color.h>

namespace ray_tracer::lighting {

struct Material{
    img::Color color;
    double ambient;
    double diffuse;
    double specular;
    double shininess;
    
    Material();


};


}