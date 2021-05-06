import Vue from 'vue'
import App from './App.vue'
import VueRouter from 'vue-router'

import vuetify from './plugins/vuetify';

import ScriptsList from './views/ScriptsList';
import ScriptView from './views/ScriptView';

Vue.use(VueRouter)
Vue.config.productionTip = false

const router = new VueRouter({
  routes:  [
    { path: '/', component: ScriptsList },
    { path: '/scriptview/', component: ScriptView, props: true },
    { path: '/scriptview/:name', component: ScriptView, props: true },
  ]
})

new Vue({
  router,
  vuetify,
  render: h => h(App)
}).$mount('#app')
