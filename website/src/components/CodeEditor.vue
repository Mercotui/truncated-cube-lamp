<template>
  <v-container>
    <v-row class="text-center">
      <v-col class="mb-4">
        <h1 class="display-2 font-weight-bold mb-3">
          Welcome to Truncated Cube Lamp
        </h1>

        <p class="subheading font-weight-regular">
          heya
        </p>

        <v-textarea solo name="input-7-4" label="Code Editor"></v-textarea>

        <v-btn elevation="2" v-on:click="save">
          Save
        </v-btn>
        <v-btn elevation="2" v-on:click="runInEmulator">
          Run in Emulator
        </v-btn>
      </v-col>
    </v-row>
  </v-container>
</template>

<script>
  export default {
    data: () => ({}),

    methods: {
      save: function () {
        console.log("Save Test Log");
      },

      runInEmulator: function () {
        console.log("Run In Emulator Test Log");
      },
    }
  }
</script>
