<template>
  <v-container>
    <canvas id="lamp_canvas" :width="width" :height="height"
            style="image-rendering: pixelated; width: 300px; height: 300px;"></canvas>
  </v-container>
</template>

<script>

export default {
  props: ["color", "pixels", "width", "height"],

  data() {
    return {}
  },

  mounted: function () {
    // initial setup once the DOM is completed
    this.$nextTick(function () {
      this.init();
    })
  },

  watch: {
    pixels: {
      deep: true,
      handler: function () {
        this.draw();
      }
    },
  },

  methods: {
    init: function () {
      this.canvas = document.getElementById('lamp_canvas');
      this.ctx = this.canvas.getContext('2d');
      this.ctx.imageSmoothingEnabled = false;

      this.canvas.addEventListener('mousedown', (e) => {
        const element_relative_x = e.offsetX;
        const element_relative_y = e.offsetY;
        const canvas_x = element_relative_x * this.canvas.width / this.canvas.clientWidth;
        const canvas_y = element_relative_y * this.canvas.height / this.canvas.clientHeight;
        const pixel_x = Math.floor(canvas_x);
        const pixel_y = Math.floor(canvas_y);
        const pixel_y_inverted = (this.height - 1) - pixel_y;

        this.$emit('setPixel', {
          x: pixel_x,
          y: pixel_y_inverted,
          color: this.color,
        });
      })

    },

    draw: function () {
      this.ctx.fillStyle = "black";
      this.ctx.fillRect(0, 0, this.width, this.height);

      for (let x = 0; x < this.width; x++) {
        for (let y = 0; y < this.height; y++) {
          // use this pixel's color as fillStyle
          this.ctx.fillStyle = this.pixels[(this.height - 1) - y][x];
          this.ctx.fillRect(x, y, 1, 1);
        }
      }
    },
  }
}
</script>
