#pragma once
#include <ray_tracer/math/tuple.h>

using ray_tracer::math::Tuple;

struct Projectile {
    Tuple pos;
    Tuple vel;

    Projectile(const Tuple& pos, const Tuple& vel) : pos(pos), vel(vel) {}
};

struct Environment {
    Tuple grav;
    Tuple wind;

    Environment(const Tuple& grav, const Tuple& wind) : grav(grav), wind(wind) {}
};

inline Projectile launch(const Projectile& p, const Environment& e) {
    Tuple pos_i = p.pos + p.vel;
    Tuple vel_i = p.vel + e.grav + e.wind;
    return Projectile(pos_i, vel_i);
}