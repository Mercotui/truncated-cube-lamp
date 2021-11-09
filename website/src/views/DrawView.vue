<template>
  <v-container>
    <v-row class="text-center">
      <DrawingGrid
        v-bind:color=color
        @colorUsed="onColorUsed($event)"
      />
      <v-color-picker
        class="ma-2"
        show-swatches
        :swatches="swatches"
        v-model="color"
      >
      </v-color-picker>
    </v-row>
  </v-container>
</template>

<script>
import DrawingGrid from '../components/DrawingGrid';

export default {
  components: {
    DrawingGrid,
  },

  props: {
    name: String
  },

  data: () => ({
    color: "#ffffff",
    defaultColor: '#f0f0f0',
    colorHistory: ['#f0f0f0', '#f0f0f0', '#f0f0f0', '#f0f0f0'],
    swatches: [
      ['#f0f0f0', '#fbf305', '#f20884', '#1fb714'],
      ['#f0f0f0', '#ff6403', '#4700a5', '#006412'],
      ['#f0f0f0', '#dd0907', '#0000d3', '#000000'],
      ['#f0f0f0', '#90713a', '#02abea', '#ffffff'],
      ],
  }),

  methods: {
    onColorUsed: function (color) {
      // remove all history entries for the current color
      this.colorHistory = this.colorHistory.filter(item => (item != color));
      // add current color to front of history
      this.colorHistory.unshift(color);
      // pad history with default color
      this.colorHistory.push(this.defaultColor, this.defaultColor, this.defaultColor);
      // truncate history
      this.colorHistory = this.colorHistory.slice(0, 4);

      // update the color picker swatches
      this.colorHistory.forEach((color, index) => {
        // turns out vue can't handle arrays.
        // Its ok, neither could I at first, take your time.
        var newval = this.swatches[index];
        newval[0] = color;
        this.$set(this.swatches, index, newval)
      });
    }
  }
};
</script>
