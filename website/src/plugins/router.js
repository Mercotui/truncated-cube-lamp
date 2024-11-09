/**
 * router/index.ts
 *
 * Automatic routes for `./src/pages/*.vue`
 */

// Composables
import {createMemoryHistory, createRouter} from 'vue-router'

// Views
import IndexView from '../views/IndexView';
import ScriptView from '../views/ScriptView';
import DrawView from '../views/DrawView';

const router = new createRouter({
    history: createMemoryHistory(),
    routes: [
        {path: '/', component: IndexView},
        {path: '/draw/', component: DrawView, props: true},
        {path: '/draw/:name', component: DrawView, props: true},
        {path: '/script/', component: ScriptView, props: true},
        {path: '/script/:name', component: ScriptView, props: true},
    ],

})

export default router
