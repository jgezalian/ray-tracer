function render() {
  const heightInput = document.getElementById("height");
  const widthInput  = document.getElementById("width");

  const height = Number(heightInput.value);
  const width  = Number(widthInput.value);
  let sc_test = null;
  let pixel_arr = null;

  const loadingContainer = document.getElementById("loading-container");

  if (loadingContainer) {
    loadingContainer.style.display = "flex";
  }

  scene_canvas_test()
    .then((Module) => {
      sc_test = Module;
      sc_test.sphere_on_plane_render_pixels = sc_test.cwrap(
        "sphere_on_plane_render_pixels",
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
      const canvas_context = canvas.getContext("2d");

      sc_test.sphere_on_plane_render_pixels(pixel_arr.byteOffset, width, height);
      const image = new ImageData(new Uint8ClampedArray(pixel_arr), width);
      canvas_context.putImageData(image, 0, 0);

      if (loadingContainer) {
        loadingContainer.style.display = "none";
      }
    })
    .catch(() => {
      if (loadingContainer) {
        loadingContainer.style.display = "none";
      }
    });
}
