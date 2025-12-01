let height = 500;
let width = 500;
let sc_test = null;
let pixel_arr = null;
scene_canvas_test().then((Module) => {
  sc_test = Module;
  sc_test.first_scene_render_pixels = sc_test.cwrap(
    "first_scene_render_pixels",
    null,
    ["number", "number", "number"]
  );
  pixel_arr = new Uint8Array(
    sc_test.HEAPU8.buffer,
    sc_test._malloc(height * width * 4),
    height * width * 4
  );
  const canvas = document.getElementById("canvas");
  canvas.width = width;
  canvas.height = height;
  canvas_context = canvas.getContext("2d");
  sc_test.first_scene_render_pixels(pixel_arr.byteOffset, width, height);
  const image = new ImageData(new Uint8ClampedArray(pixel_arr), width);
  canvas_context.putImageData(image, 0, 0);
});
