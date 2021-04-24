<template>
  <v-container>
    <v-row class="text-center">
      <v-col class="mb-4">
        <p class="subheading font-weight-regular">
          heya
        </p>
        <v-btn elevation="2" v-on:click="save">
          Save
        </v-btn>
        <v-btn elevation="2" v-on:click="runInEmulator">
          Run in Emulator
        </v-btn>

        <v-textarea solo v-model="text_editor" name="input-7-4" label="Code Editor"></v-textarea>
      </v-col>
    </v-row>
  </v-container>
</template>

<script>
  export default {
    data() {
      return {
        text_editor: "screen.setPixel(0, 0, 'red');\nscreen.setPixel(2, 5, 'green');\nscreen.setPixel(6, 6, 'blue');\nscreen.draw();",
      }
    },

    methods: {
      save: function () {
        console.log("Save Test Log");
      },

      runInEmulator: function () {
        this.$emit('runInEmulator', this.text_editor)
      },
    }
  }
</script>
