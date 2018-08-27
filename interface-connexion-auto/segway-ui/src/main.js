// The Vue build version to load with the `import` command
// (runtime-only or standalone) has been set in webpack.base.conf with an alias.
import Vuex from 'vuex'
import Vue from 'vue'
import App from './App'
import Vuetify from 'vuetify'
import { createSocketioPlugin } from 'vuex-socketio-plugin'
import 'vuetify/dist/vuetify.min.css'

Vue.use(Vuetify)
Vue.use(Vuex)

Vue.config.productionTip = false

const store = new Vuex.Store({
  plugins: [createSocketioPlugin('http://localhost:3000')],
  state: {
    _client: null,
    angle: 0,
    vitesse_angulaire: 0,
    vitesse_lineaire: 0,
    battery: null,
    userPresence: false,
    connected: false
  },
  mutations: {
    SOCKET_CONNECT (state, { client }) {
      console.log('Connected')
      state._client = client
      state.connected = true
    },

    SOCKET_test (state, { data }) {
      let obj = data[0]
      obj = JSON.parse(obj)
      state.angle = obj.position_angulaire
      state.vitesse_angulaire = obj.vitesse_angulaire
      state.vitesse_lineaire = obj.vitesse_lineaire
      state.battery = obj.battery
    },

    SOCKET_DISCONNECT (state, { data }) {
      console.log('Disconnected')
      state._client = null
      state.connected = false
    }
  },
  actions: {
    send (context, {topic, data}) {
      console.log('ici')
      console.log(data)
      if (!context.state._client) {
        throw new Error("don't have connection")
      }
      context.state._client.emit(topic, data)
    }
  }
})
/* eslint-disable no-new */
new Vue({
  el: '#app',
  store,
  components: { App },
  template: '<App/>'
})
