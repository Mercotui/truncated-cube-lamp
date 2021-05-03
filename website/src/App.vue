<template>
  <v-app>
    <v-app-bar
      app
      color="primary"
      dark
    >
      <div class="d-flex align-center">
        <v-img
          alt="Vuetify Logo"
          class="shrink mr-2"
          contain
          src="https://cdn.vuetifyjs.com/images/logos/vuetify-logo-dark.png"
          transition="scale-transition"
          width="40"
        />

        <v-img
          alt="Vuetify Name"
          class="shrink mt-1 hidden-sm-and-down"
          contain
          min-width="100"
          src="https://cdn.vuetifyjs.com/images/logos/vuetify-name-dark.png"
          width="100"
        />
      </div>
    </v-app-bar>

    <v-main>
      <v-row class="text-center">
        <v-col class="mb-4">
          <h1 class="display-2 font-weight-bold mb-3">
            Welcome to Truncated Cube Lamp
          </h1>
        </v-col>
      </v-row>

      <ScriptsList/>
      <CodeEditor @runInEmulator="runInEmulator" />
      <LampEmulator/>
    </v-main>
  </v-app>
</template>

<script>
import ScriptsList from './components/ScriptsList';
import CodeEditor from './components/CodeEditor';
import LampEmulator from './components/LampEmulator';

export default {
  name: 'App',

  components: {
    ScriptsList,
    CodeEditor,
    LampEmulator,
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
