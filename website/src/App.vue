<template>
  <v-app>
    <v-app-bar app color="primary" dark>
      <router-link to="/">
          <v-img
            alt="Logo"
            to="/"
            class="shrink mx-4"
            contain
            :src="require('./assets/logo.svg')"
            transition="scale-transition"
            width="25"
          />
        </router-link>
        <v-app-bar-title>Truncated Cube Lamp</v-app-bar-title>
    </v-app-bar>

    <v-main>
      <v-container fluid>
        <router-view></router-view>
      </v-container>
    </v-main>
  </v-app>
</template>

<script>

export default {
  name: 'App',
};
</script>
