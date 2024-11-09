// Plugins
import { registerPlugins } from '@/plugins'

// Components
import App from './App.vue'

// Composables
import { createApp } from 'vue'
import {makeServer} from "./mock-server"

if (import.meta.env.DEV && import.meta.env.MODE !== "online") {
  // If we are in development mode, and not using a proxy for our API calls, then start a mock API server
  makeServer()
}

const app = createApp(App)

registerPlugins(app)

app.mount('#app')
