// Plugins
import Vue from '@vitejs/plugin-vue'
import Vuetify, {transformAssetUrls} from 'vite-plugin-vuetify'
import ViteFonts from 'unplugin-fonts/vite'

// Utilities
import {defineConfig, loadEnv} from 'vite'
import {fileURLToPath, URL} from 'node:url'

// https://vitejs.dev/config/
export default defineConfig(({mode}) => {
    const env = loadEnv(mode, process.cwd())
    return {
      plugins: [
        Vue({
          template: {transformAssetUrls}
        }),
        // https://github.com/vuetifyjs/vuetify-loader/tree/master/packages/vite-plugin#readme
        Vuetify({
          autoImport: true,
        }),
        ViteFonts({
          google: {
            families: [{
              name: 'Roboto',
              styles: 'wght@100;300;400;500;700;900',
            }],
          },
        }),
      ],
      define: {'process.env': {}},
      resolve: {
        alias: {
          '@': fileURLToPath(new URL('./src', import.meta.url))
        },
        extensions: [
          '.js',
          '.json',
          '.jsx',
          '.mjs',
          '.ts',
          '.tsx',
          '.vue',
        ],
      },
      server: {
        port: 3000,
        // If we are in online development mode, then start an API proxy
        ... env.MODE === "online" ? {
          proxy: {
            '/api': {
              target: env.VITE_API_URL,
              changeOrigin: true,
              secure: true,
            },
          },
        } : {}
      },
    }
  }
)
