<template>
    <div class="led" v-bind:class="{ ledOn: this.value, ledOff: !this.value}">{{label}}</div>
</template>

<script>
export default {
    props: ['size', 'value', 'label'],
    data: () => {
        return {
            circle: null
        }
    },
    mounted () {
        this.circle = this.$el
        if (this.size != null) {
            this.$el.style.width = this.size + 'px'
            this.$el.style.height = this.size + 'px'
        } else {
            this.$el.style.width = '50px'
            this.$el.style.height = '50px'
        }
    }
}
</script>

<style>
    .led{
        border-radius: 50%;
        border:4px solid black;
        padding-top : 5px; 
    }
    .ledOn{
        background-color: lightgreen;

    }
    .ledOff{
        background-color: red;
    }
</style>

