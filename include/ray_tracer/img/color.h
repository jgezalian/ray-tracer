#pragma once
#include <cmath>

namespace ray_tracer::img {
struct Color
{
    double r;
    double g;
    double b;

    Color(double r = 0.0, double g = 0.0, double b = 0.0) : r(r), g(g), b(b) {};
};

inline Color operator+(const Color &c1, const Color &c2) {
    return Color(c1.r + c2.r, c1.g + c2.g, c1.b + c2.b);
}

inline Color operator-(const Color &c1, const Color &c2) {
    return Color(c1.r - c2.r, c1.g - c2.g, c1.b - c2.b);
}

inline Color operator*(const Color &c, const double scalar) {
    return Color(c.r * scalar, c.g * scalar, c.b * scalar);
}

inline Color operator*(const double scalar, const Color &c) {
    return c * scalar;
}

inline Color operator*(const Color &c1, const Color &c2) {
    return Color(c1.r * c2.r, c1.g * c2.g, c1.b * c2.b);
}

inline Color operator/(const Color &c, const double scalar) {
    return Color(c.r/scalar, c.g/scalar, c.b/scalar);
}

inline Color operator-(const Color &c) {
    return Color(-1 * c.r, -1 * c.g, -1 * c.b);
}

inline bool operator==(const Color &c1, const Color &c2) {
    return (c1.r == c2.r && c1.g == c2.g && c1.b == c2.b);
}
}