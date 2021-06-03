<template>
  <v-container>
    <v-row class="text-center">
      <v-col class="mb-4">
        <h1 class="display-2 font-weight-bold mb-3">
          Lamp Emulator
        </h1>

        <canvas id="lamp_canvas" width="300" height="300"></canvas>

        <v-switch
          v-model="blur_lamp_switch"
          label="Blur">
        </v-switch>
      </v-col>
    </v-row>
  </v-container>
</template>

<script>
  const lamp_renderer = {
    canvas: undefined,
    ctx: undefined,
    width: 1,
    height: 1,
    emulated_width: 8,
    emulated_height: 8,
    emulated_pixel_size: 1,
    resolution: undefined,
    pixels: undefined,

    init: function () {
      this.canvas = document.getElementById('lamp_canvas');
      this.ctx = this.canvas.getContext('2d');
      this.width = this.canvas.offsetWidth;
      this.height = this.canvas.offsetHeight;

      var emulated_pixel_width = this.width / this.emulated_width;
      var emulated_pixel_height = this.height / this.emulated_height;
      this.emulated_pixel_size = Math.min(emulated_pixel_width, emulated_pixel_height);

      this.pixels = new Array(this.emulated_width * this.emulated_height);
      this.pixels.fill("black");

      this.resolution = {width: this.emulated_width, height: this.emulated_height};

      this.canvas.addEventListener('resize', function(){
        this.width = this.canvas.offsetWidth;
        this.height = this.canvas.offsetWidth;

        var emulated_pixel_width = this.width / this.emulated_width;
        var emulated_pixel_height = this.height / this.emulated_height;
        this.emulated_pixel_size = Math.min(emulated_pixel_width, emulated_pixel_height);
      }, false);

      lamp_renderer.draw();
    },

    draw: function () {
      this.ctx.fillStyle = "black";
      this.ctx.fillRect(0, 0, this.width, this.height);

      for (let x = 0; x < this.width; x++) {
        for (let y = 0; y < this.height; y++) {
          const canvas_x = x * this.emulated_pixel_size;
          const canvas_y = y * this.emulated_pixel_size;
          const color = this.pixels[(y * this.emulated_width) + x];

          this.ctx.fillStyle = color;
          this.ctx.fillRect(canvas_x, canvas_y, this.emulated_pixel_size, this.emulated_pixel_size);
        }
      }
    },

    setPixel: function (x, y, color){
      this.pixels[(y * this.emulated_width) + x] = color;
    },

    clear: function () {
      this.pixels.fill("black");
    },
  };

  export default {
    data () {
      return {
        blur_lamp_switch: false,
      }
    },

    mounted: function () {
      // initial setup once the DOM is completed
      this.$nextTick(function () {
        lamp_renderer.init();
      })
    },

    run: function (animation_script) {
        lamp_renderer.clear();

        try {
          var animation_func = Function('screen', '"use strict";' + animation_script);
          animation_func(lamp_renderer);
        } catch(err) {
          // TODO: add this to the UI?
          console.log(err.toString())
        }
    },
  }
</script>
