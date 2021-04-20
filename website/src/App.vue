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
      <CodeEditor/>

      <LampEmulator/>
    </v-main>
  </v-app>
</template>

<script>
import CodeEditor from './components/CodeEditor';
import LampEmulator from './components/LampEmulator';

export default {
  name: 'App',

  components: {
    CodeEditor,
    LampEmulator,
  },

  data: () => ({
    //
  }),
};
</script>
