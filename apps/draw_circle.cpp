#include <ray_tracer/img/canvas.h>
#include <ray_tracer/img/color.h>
#include <ray_tracer/math/tuple.h>
#include <ray_tracer/math/matrix.h>
#include <ray_tracer/math/transform.h>
#include <ray_tracer/math/ray.h>
#include <ray_tracer/geometry/intersection.h>
#include <iostream>

using ray_tracer::img::Canvas;
using ray_tracer::img::Color;
using ray_tracer::math::Tuple;
using ray_tracer::math::Matrix;
using ray_tracer::math::point;
using ray_tracer::math::rotate_z;
using ray_tracer::math::inverse;
using ray_tracer::math::scaling;
using ray_tracer::math::translation;


void draw_circle(const Canvas &canvas) {
    const Matrix translate = translation(canvas.width/2 - 1, canvas.height/2 - 1, 0);
    const Sphere
}