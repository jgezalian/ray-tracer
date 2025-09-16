#include <ray_tracer/img/canvas.h>

#include <algorithm>
#include <cmath>
#include <fstream>
#include <iostream>
#include <string>

namespace ray_tracer::img {

// initalize canvas of width x height with all black pixels
Canvas::Canvas(int width, int height)
    : width(width),
      height(height),
      pixels(height, std::vector<Color>(width, Color(0.0, 0.0, 0.0))) {}

void Canvas::write_pixel(int x, int y, const Color& c) {
    if (x < 0 || y < 0 || y >= height || x >= width) return;
    pixels[y][x] = c;
}

void write_ppm(const std::string& ppm_text) {
    std::ofstream outfile("generated_images/projectile.ppm");
    outfile << ppm_text << '\n';
    outfile.close();
}

std::string canvas_to_ppm(const Canvas& canvas) {
    int MAX_CHAR_LINE = 70;
    int line_width = 0;
    std::string ppm_text{std::string("P3\n") + std::to_string(canvas.width) + std::string(" ") +
                         std::to_string(canvas.height) + std::string("\n255\n")};

    auto ppm_append = [&](int rgb_val) {
        std::string next_token = std::to_string(limit255(rgb_val));
        int next_len =
            (line_width == 0 ? 0 : 1) + next_token.length(); /* +1 to count leading space when
                                                                writing past first val*/
        if (line_width + next_len > MAX_CHAR_LINE) {
            ppm_text.push_back('\n');
            line_width = 0;
        }
        if (line_width > 0) {
            ppm_text.push_back(' ');
            ++line_width;
        }
        ppm_text += next_token;
        line_width += next_token.length();
    };

    for (const auto& row : canvas.pixels) {
        for (const auto& pixel : row) {
            int r = static_cast<int>(std::round(pixel.r * 255.0));
            int g = static_cast<int>(std::round(pixel.g * 255.0));
            int b = static_cast<int>(std::round(pixel.b * 255.0));
            ppm_append(r);
            ppm_append(g);
            ppm_append(b);
        }
        line_width = 0;
        ppm_text.push_back('\n');
    }

    return ppm_text;
}

}  // namespace ray_tracer::img