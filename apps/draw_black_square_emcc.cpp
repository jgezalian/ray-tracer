#include <ray_tracer/img/canvas.h>


using ray_tracer::img::Canvas;

int main(){
    Canvas canvas{100, 100};
    std::string ppm_string = canvas_to_ppm(canvas);
    ray_tracer::img::write_ppm(ppm_string, "black_canvas");
    return 0;
}