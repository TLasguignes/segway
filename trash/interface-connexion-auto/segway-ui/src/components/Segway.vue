<template>
<v-container fluid>
    <v-slide-y-transition mode="out-in">
      <v-layout column align-center>
        <img id="seg_ico" v-bind:style="computed_angle" src="@/assets/segway_naze.svg" alt="Une représentation artistique d'un segway">
        Angle : {{angle}} deg
      </v-layout>
    </v-slide-y-transition>
  </v-container>
</template>

<script>

export default {
    data: function () {
        return {
            angle: 0
        }
    },
    computed: {
        computed_angle () {
            return {transform: 'rotate(' + this.$store.state.angle + 'deg)'}
        }
    }
}
</script>


<style>
    #seg_ico{
        transform-origin: center;
    }
</style>
