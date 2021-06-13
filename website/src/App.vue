<template>
  <v-app>
    <v-app-bar app color="primary" dark>
      <router-link to="/">
          <v-img
            alt="Logo"
            to="/"
            class="shrink mx-4 rainbow-on-hover"
            contain
            :src="require('./assets/logo.svg')"
            transition="scale-transition"
            width="30"
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

<style media="screen">
.rainbow-on-hover:hover {
  animation: rainbow 1s steps(36);
  animation-fill-mode: forwards
}

@keyframes rainbow {
0% { filter:invert(15%) sepia(0%) saturate(0%) hue-rotate(0deg) brightness(0%) contrast(116%); }
10% { filter:invert(15%) sepia(95%) saturate(6489%) hue-rotate(0deg) brightness(80%) contrast(116%); }
80% { filter:invert(15%) sepia(95%) saturate(6489%) hue-rotate(360deg) brightness(80%) contrast(116%); }
100% { filter:invert(100%) sepia(95%) saturate(100%) hue-rotate(360deg) brightness(100%) contrast(116%); }
}
</style>

<script>

export default {
  name: 'App',
};
</script>
