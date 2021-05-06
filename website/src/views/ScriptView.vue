<template>
  <v-container>
    <v-row class="text-center">
      <v-col class="mb-4">
        <CodeEditor v-bind:script_name=name @runInEmulator="runInEmulator" />
      </v-col>
      <v-col class="mb-4">
        <LampEmulator/>
      </v-col>
    </v-row>
  </v-container>
</template>

<script>
import CodeEditor from '../components/CodeEditor';
import LampEmulator from '../components/LampEmulator';

export default {
  components: {
    CodeEditor,
    LampEmulator,
  },

  props: {
    name: String
  },

  data: () => ({
    //
  }),

  methods: {
    runInEmulator: function (animation_script) {
      LampEmulator.run(animation_script)
    }
  },
};
</script>
