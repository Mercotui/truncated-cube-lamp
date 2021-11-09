<template>
  <v-container>
    <canvas id="lamp_canvas" width="8" height="8" style="image-rendering: pixelated; width: 300px; height: 300px;"></canvas>
  </v-container>
</template>

<script>
  export default {
    props: ["color"],

    data () {
      return {
        pixels: []
      }
    },

    mounted: function () {
      // initial setup once the DOM is completed
      this.$nextTick(function () {
        this.init();
        this.draw();
      })
    },

    methods: {
      init: function () {
        this.canvas = document.getElementById('lamp_canvas');
        this.ctx = this.canvas.getContext('2d');
        this.ctx.imageSmoothingEnabled = false;
        this.width = 8;
        this.height = 8;
        this.display_width = this.canvas.offsetWidth;
        this.display_height = this.canvas.offsetHeight;

        this.display_pixel_width = this.display_width / this.width;
        this.display_pixel_height = this.display_height / this.height;

        for (var y = 0; y < this.height; y++) {
          this.pixels[y] = []
          for (var x = 0; x < this.height; x++) {
            this.pixels[y][x] = '#000'
          }
        }
        this.canvas.addEventListener('mousedown', (e) => {
          const element_relative_x = e.offsetX;
          const element_relative_y = e.offsetY;
          const canvas_x = element_relative_x * this.canvas.width / this.canvas.clientWidth;
          const canvas_y = element_relative_y * this.canvas.height / this.canvas.clientHeight;
          const pixel_x = Math.floor(canvas_x);
          const pixel_y = Math.floor(canvas_y);

          this.setPixel(pixel_x, pixel_y, this.color);
          this.draw();
        })

      },

      draw: function () {
        this.ctx.fillStyle = "black";
        this.ctx.fillRect(0, 0, this.width, this.height);

        for (let x = 0; x < this.width; x++) {
          for (let y = 0; y < this.height; y++) {
            var color = this.pixels[y][x];
            this.ctx.fillStyle = color;
            this.ctx.fillRect(x, y, 1, 1)
          }
        }
      },

      setPixel: function (x, y, color) {
        this.pixels[y][x] = color

        // notify parent about the color usage
        this.$emit('colorUsed', color)
      }
    }
  }
</script>
