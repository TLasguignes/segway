<template>
    <div :class="['gamepad-button', buttonType]">
        <p @click="buttonHandler" v-if="buttonType=='circle'" >○</p>
        <p @click="buttonHandler" v-else-if="buttonType=='square'">□</p>
        <p @click="buttonHandler" v-else-if="buttonType=='cross'">X</p>
        <p @click="buttonHandler" v-else-if="buttonType=='triangle'">△</p>
    </div>
</template>

<script>
export default {
    props: ['buttonType'],
    methods: {
        buttonHandler: function() {
            this.$store.dispatch({
                type: 'send',
                data: this.buttonType,
                topic: 'button'
            })
        }
    }
}
</script>

<style>
.gamepad-button{
   background-color: #414449;
   border-radius: 100%;
   width: 70px;
   height: 70px;
   text-align: center;
}

.square{
    line-height: 60px;
    font-size: 50px;
    color: #e771f2;
}

.circle{
    line-height: 60px;
    font-size: 60px;
    color: #e02323;
}

.cross{
    line-height: 70px;
    font-size: 50px;
    color: #5178ba;   
}

.triangle{
    line-height: 50px;
    font-size: 60px;
    color: #39b21e;
}

</style>

