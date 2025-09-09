#pragma once
#include "color.h"
#include <cmath>
#include <fstream>
#include <vector>

namespace ray_tracer::img {

struct Canvas {
  int width;
  int height;
  std::vector<std::vector<Color>> pixels;

  // initalize canvas of width x height with all black pixels
  Canvas(int width, int height);

  void write_pixel(int x, int y, const Color &c);
};

inline constexpr int limit255(int rgb_val) noexcept {
  return rgb_val < 0 ? 0 : (rgb_val > 255 ? 255 : rgb_val);
}

void write_ppm(const std::string &ppm_text);
std::string canvas_to_ppm(const Canvas &canvas);
} // namespace ray_tracer::img
