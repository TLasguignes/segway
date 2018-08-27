const net = require('net')
const EventEmitter = require('events');

const client = new net.Socket();
client.setEncoding('utf8')
let connectionState = false;
/*Une fonction qui retourne un callback et le client lorsque la connection est réussi*/
const eventObj = new EventEmitter();
let nbrErr = 0;


function connect(ip, port, interval, callback){
    if(connectionState==false){
        let connectTry = setInterval(()=>{
            client.connect(port, ip, (err)=>{
                if(!connectionState && !err){
                    clearInterval(connectTry);
                    connectionState=true;
                    callback(client);
                }
            });       
        }, interval);
    }
}

client.on('error', (err)=>{
    nbrErr++;
    console.log(`Serveur non trouvé ${nbrErr}`);
});

client.on('close', ()=>{
    if(connectionState==true){
        connectionState=false;
        eventObj.emit("close");
        nbrErr = 0;
    }
});

client.on('data', (data)=>{
    eventObj.emit("data",data)
});

module.exports = {
    client: client,
    tryConnect: connect,
    event: eventObj
}
