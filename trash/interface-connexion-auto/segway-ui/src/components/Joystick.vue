<template>
    <div id="left"></div>
</template>

<script>
import Nipple from 'nipplejs'
export default {
    data: () => {
        return {
        }
    },
    mounted: function () {
        const manager = Nipple.create({
            zone: document.getElementById('left'),
            mode: 'static',
            position: { left: '20%', top: '50%' },
            color: 'black',
            size: 200
        })
        manager.on('move', this.eventCallBack)
    },
    methods: {
        eventCallBack: function (evt, data) {
            let x = data.distance * Math.cos(data.angle.radian)
            let y = data.distance * Math.sin(data.angle.radian)
            console.log(`{ x : ${x}, y : ${y}`)
            let json = {}
            json['x'] = x
            json['y'] = y
            this.$store.dispatch({
                type: 'send',
                data: json,
                topic: 'joystick'
            })
        }
    }
}
</script>

<style>

</style>
