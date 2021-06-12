import Vue from 'vue';
import Vuetify from 'vuetify/lib/framework';

Vue.use(Vuetify);

const dark_theme_query = window.matchMedia('(prefers-color-scheme: dark)')

export default new Vuetify({
  theme: {
    dark: dark_theme_query.matches,
    themes: {
      light: {
        primary: "#B87333",
        secondary: "#3378B8",
        accent: "#b8b633",
        error: "#b83335",
        success: "#78b833",
      },
      dark: {
        primary: "#B87333",
        secondary: "#3378B8",
        accent: "#b8b633",
        error: "#b83335",
        success: "#78b833",
      },
    },
  },
});

dark_theme_query.addEventListener('change', (dark_theme_event) => {
  Vuetify.framework.theme.dark = dark_theme_event.matches
})
