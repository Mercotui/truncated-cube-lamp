import Vue from 'vue'
import App from './App.vue'
import VueRouter from 'vue-router'

import vuetify from './plugins/vuetify';
import {makeServer} from "./server"

import ScriptsList from './views/ScriptsList';
import ScriptView from './views/ScriptView';
import DrawView from './views/DrawView';

Vue.use(VueRouter)
Vue.config.productionTip = false

const router = new VueRouter({
  routes:  [
    { path: '/', component: ScriptsList },
    { path: '/drawing/', component: DrawView, props: true },
    { path: '/scriptview/', component: ScriptView, props: true },
    { path: '/scriptview/:name', component: ScriptView, props: true },
  ]
})

if (process.env.NODE_ENV === "development") {
  makeServer()
}

new Vue({
  router,
  vuetify,
  render: h => h(App)
}).$mount('#app')
