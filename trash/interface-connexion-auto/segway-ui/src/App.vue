<template>
  <v-app light>
    <v-toolbar>
      <v-toolbar-title class="test"> Segway Application</v-toolbar-title>
    </v-toolbar>
    <v-content>
      <!-- Layout smartphone -->
      <v-container hidden-sm-and-up grid-list-xs text-xs-center>
        <h2>En mode paysage !</h2>
        <p></p>
        <p>Tournez votre téléphone en mode paysage pour pouvoir profiter de l'application.</p>
        <p>Ou alors ... la taille de votre écran est vraiment trop petite...</p>
        <img src="@/assets/rotate.gif" alt="Rotate phone">
      </v-container>

      <v-container hidden-xs-only hidden-md-and-up grid-list-sm text-sm-center>
        <v-layout >
          <v-flex offset-xs9>
             <v-switch label="Take Control"> </v-switch>
          </v-flex></v-layout>
        <v-layout><v-flex xs6 class="zone-joystick"> 
            <v-layout>
              <Joystick/>
            </v-layout>
          </v-flex>
           <v-flex class="zone-bouttons">
            <v-layout>
                <v-flex offset-xs4><GameButton buttonType="triangle"/></v-flex>
               </v-layout> 
             <v-layout>
               <v-flex offset-xs1><GameButton buttonType="square"/></v-flex>
               <v-flex offset-xs1><GameButton buttonType="circle"/></v-flex>
               </v-layout> 
              <v-layout>
                <v-flex offset-xs4><GameButton buttonType="cross"/></v-flex>
               </v-layout> 
            </v-flex></v-layout>
      </v-container>
      
      <!-- Layout Application -->
      <v-container hidden-sm-and-down grid-list-sm text-sm-center>
        <v-layout >
          <v-flex sm5>
            <h1 class="zone2">SALUT</h1>
            <v-flex offset-sm4><Gauge data_store="vitesse_angulaire" label="Angular Speed" unit="rad/s"/></v-flex>
            <v-flex offset-sm4><Gauge data_store="vitesse_lineaire" label="Linear Speed" unit="Km/h"/></v-flex>
            <v-flex offset-sm4><Gauge data_store="battery" label="Battery Voltage" unit="%"/></v-flex>
            <v-flex offset-sm4><Led :value="this.$store.state.connected" label="App"/></v-flex>
            <v-flex offset-sm4><Led :value="this.$store.state.user" label="User"/></v-flex>
            <v-flex offset-sm4><Led :value="this.$store.state.user" label="Emerg"/></v-flex>
          </v-flex>
          <v-flex sm7> <h1 class="zone1">FOEAOFEAFE</h1>
            <SegAngle/>
          </v-flex>
        </v-layout>
        <v-layout><v-flex><h1 class="zone3">Console</h1></v-flex></v-layout>
      </v-container>


      
    </v-content>
    <v-footer app>
      <v-spacer/>
      <span>INSA Toulouse &copy; 2018</span>
      <v-spacer/>
    </v-footer>
  </v-app>
</template>

<script>
import Error from './components/Error'
import SegAngle from './components/Segway'
import Gauge from './components/Gauge'
import Joystick from './components/Joystick'
import GameButton from './components/Button'
import Led from './components/Led'

export default {
  data () {
    return {
    }
  },
  computed: {
    test: function () {
      return [this.$store.state.vitesse_angulaire]
    }
  },
  name: 'SegwayUI',
  components: {
    Error,
    SegAngle,
    Gauge,
    Joystick,
    GameButton,
    Led
  }
}
</script>

<style>
  .zone1{
    background-color: #9ef7a2;
  }
  .zone2{
    background-color: #f2bf9b;
  }
  .zone3{
    background-color: lightblue;
  }

  .test{
    width: 100%;
    color: rgba(175, 47, 47, 0.30);
    text-rendering: optimizeLegibility;
  }
</style>

