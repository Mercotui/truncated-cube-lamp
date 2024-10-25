/**
 * plugins/vuetify.js
 *
 * Framework documentation: https://vuetifyjs.com`
 */

// Styles
import '@mdi/font/css/materialdesignicons.css'
import 'vuetify/styles'

// Composables
import {createVuetify} from 'vuetify'

const dark_theme_query = window.matchMedia('(prefers-color-scheme: dark)')

// https://vuetifyjs.com/en/introduction/why-vuetify/#feature-guides
export default createVuetify({
  theme: {
    defaultTheme: 'dark',
    dark: dark_theme_query.matches,
    themes: {
      light: {
        colors: {
          primary: "#B87333",
          secondary: "#3378B8",
          accent: "#b8b633",
          error: "#b83335",
          success: "#78b833",
        },
      },
      dark: {
        colors: {
          primary: "#B87333",
          secondary: "#3378B8",
          accent: "#b8b633",
          error: "#b83335",
          success: "#78b833",
        },
      },
    },
  },
})
