// Plugins
import { registerPlugins } from '@/plugins'

// Components
import App from './App.vue'

// Composables
import { createApp } from 'vue'
import {makeServer} from "./mock-server"

if (process.env.NODE_ENV === "development") {
  makeServer()
}

const app = createApp(App)

registerPlugins(app)

app.mount('#app')
