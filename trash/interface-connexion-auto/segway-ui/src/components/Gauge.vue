<template>
<div class="test">
    <canvas class="gauge"></canvas>
    <span class="percent">{{changingData}} {{unit}}</span>
    <h3 class="label">{{this.label}}</h3>
</div>
</template>

<script>
import { Gauge } from 'gaugeJS'

export default {
  data: () => {
      return {
          gauge: null
      }
  },
  props: ['data_store', 'label', 'unit'],
  mounted () {
    let opts = {
      angle: 0, // The span of the gauge arc
      colorStart: '#6F6EA0',   // Colors
      colorStop: '#C0C0DB',    // just experiment with them
      strokeColor: '#EEEEEE',  // to see which ones work best for you
      generateGradient: true,
      pointer: {
            length: 0.53, // // Relative to gauge radius
            strokeWidth: 0.057, // The thickness
            color: '#000000' // Fill color
        }
    }

    this.gauge = new Gauge(this.$el.firstChild).setOptions(opts) // create sexy gauge!

    this.gauge.animationSpeed = 1
    this.gauge.maxValue = 100
    this.gauge.set(0) // set actual value
  },
  computed: {
      changingData: function () {
          if (this.gauge !== null) {
              this.gauge.set(this.$store.state[this.data_store])
          }
          return this.$store.state[this.data_store]
      }
  }
}
</script>

<style>
.label{
    display: block;
    text-align: center;
}
.percent{
    display: block;
    text-align: center;
    font-weight: bold;
}
.gauge{
    width: 100%;
}
.test{
    width: 200px;
}
</style>


