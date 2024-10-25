<script setup>
definePage({
  alias: ['/draw/:name'],
})
</script>

<template>
  <v-container>
    <v-row class="text-center">
      <v-col class="mb-4">
        <div class="text-center">
          <v-btn class="mx-1" elevation="2" :disabled="!save_enabled" v-on:click="save">Save</v-btn>
          <v-btn class="mx-1" elevation="2" v-on:click="save_overlay_opened = true">Save As</v-btn>
          <v-btn class="mx-1" elevation="2" :disabled="!delete_enabled" color="error" v-on:click="delete_overlay_opened = true">Delete</v-btn>
          <v-btn class="mx-1" :elevation="live_drawing_button_elevation" :color="live_drawing_button_color" v-on:click="live_drawing_enabled = !live_drawing_enabled">Live</v-btn>
        </div>

        <DrawingGrid
        v-bind:color="color"
        v-bind:pixels="pixels"
        v-bind:width="width"
        v-bind:height="height"
        @setPixel="setPixel($event)"
        />

        <v-color-picker
        class="ma-2"
        show-swatches
        :swatches="swatches"
        v-model="color"
        />

        <v-overlay :value="save_overlay_opened">
          <v-card class="mx-auto my-12" max-width="374">
            <v-card-title>Enter Script Name</v-card-title>
            <v-text-field label="Script Name" v-model="name" solo></v-text-field>
            <v-card-actions>
              <v-btn @click="save_overlay_opened = false">
                Cancel
              </v-btn>
              <v-btn color="success" @click="saveAs">
                Save
              </v-btn>
            </v-card-actions>
          </v-card>
        </v-overlay>

        <v-overlay :value="delete_overlay_opened">
          <v-card class="mx-auto my-12" max-width="374">
            <v-card-title>Delete {{name}} ?</v-card-title>
            <v-card-actions>
              <v-btn @click="delete_overlay_opened = false">
                Cancel
              </v-btn>
              <v-btn color="error" @click="deleteScript">
                Delete
              </v-btn>
            </v-card-actions>
          </v-card>
        </v-overlay>
      </v-col>
    </v-row>
  </v-container>
</template>

<script>
import axios from 'axios';
import base64 from 'base-64';
import utf8 from 'utf8';
import DrawingGrid from '../components/DrawingGrid';
import _ from 'lodash';
import chroma from "chroma-js";

export default {
  components: {
    DrawingGrid,
  },

  props: {
    name: String
  },

  data: function () {
    return {
      save_overlay_opened: false,
      delete_overlay_opened: false,
      live_drawing_enabled: true,
      width: 8,
      height: 8,
      pixels: [],
      content: "",
      type: ["template"],
      color: "#ffffff",
      defaultColor: '#f0f0f0',
      colorHistory: ['#f0f0f0', '#f0f0f0', '#f0f0f0', '#f0f0f0'],
      swatches: [
        ['#f0f0f0', '#fbf305', '#f20884', '#1fb714'],
        ['#f0f0f0', '#ff6403', '#4700a5', '#006412'],
        ['#f0f0f0', '#dd0907', '#0000d3', '#000000'],
        ['#f0f0f0', '#90713a', '#02abea', '#ffffff'],
        ],
    }
  },

  computed: {
    save_enabled: function () {
      return !(this.type.includes("default") || this.type.includes("template") || this.name  === "")
    },
    delete_enabled: function () {
      return !(this.type.includes("default") || this.type.includes("template"))
    },
    live_drawing_button_elevation: function () {
      return this.live_drawing_enabled ? "0" : "2";
    },
    live_drawing_button_color: function() {
      return this.live_drawing_enabled ? "primary" : "";
    }
  },

  created: function() {
    // create a debounced live drawing function
    this.debouncedDrawLive = _.debounce(this.drawLive, 1000, {maxWait: 1500, leading: true, trailing: true});
  },

  mounted() {
    // get script
    axios.get('/api/scripts/' + this.name + '/').then(response => {
      var bytes = base64.decode(response.data.script);
      this.content = utf8.decode(bytes);
      this.type = response.data.type
      this.pixels = this.extractPixels(this.content);
    });
  },

  methods: {
    colorUsed: function (color) {
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
    },

    setPixel: function (args) {
      // need to set array like this to notify Vue the property has changed
      const updated_row = this.pixels[args.y];
      updated_row[args.x] = args.color;
      this.$set(this.pixels, args.y, updated_row);

      this.colorUsed(args.color);

      if (this.live_drawing_enabled) {
        this.debouncedDrawLive();
      }
    },

    composeScript: function () {
      var replacement_line = '    this.pixels = ['
      for (var x = 0; x < this.width; x++) {
        replacement_line += '['
        for (var y = 0; y < this.height; y++) {
          replacement_line += '"' + this.pixels[y][x] + '",'
        }
        replacement_line += '],'
      }
      replacement_line += '];';


      var lines = this.content.split('\n');
      lines = lines.map(line => line.includes("this.pixels = ") ? replacement_line : line);
      return lines.join('\n');
    },

    extractPixels: function (script) {
      var lines = script.split('\n');
      var pixels_string = lines.find(line => line.includes("this.pixels = "));
      pixels_string = pixels_string.split('=')[1]
      var create_pixel_array = Function('"use strict";\nreturn ' + pixels_string);
      var pixels = create_pixel_array();

      if (!Array.isArray(pixels)){
        console.log("script's pixel format was not array");
        return undefined
      }
      if (!pixels.flat().every(value => chroma.valid(value))) {
        console.log("script's contains non-color pixel values");
        return undefined
      }

      return pixels;
    },

    save: function () {
      var script = this.composeScript()
      var bytes = utf8.encode(script);
      var encoded_script = base64.encode(bytes);

      axios.put('/api/scripts/' + this.name + '/', {
        name: this.name,
        script: encoded_script,
        type: this.type,
      });
    },

    saveAs: function () {
      this.save_overlay_opened = false;
      this.type = ["image"]
      this.save();
      this.$router.push('/drawing/' + this.name);
    },

    deleteScript: function () {
      axios.delete('/api/scripts/' + this.name + '/').then(() => {
        this.$router.push('/');
      });
    },

    drawLive: function () {
      var script = this.composeScript()
      var bytes = utf8.encode(script);
      var encoded_script = base64.encode(bytes);
      const name = 'image_live_draw';

      axios.put('/api/scripts/' + name + '/', {
        name: name,
        script: encoded_script,
        type: ["image", "temporary"]
      }).then(() => {
        axios.put('/api/runner/run/', {
          name: name
        });
      });
    },
  }
};
</script>
