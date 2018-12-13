
const express = require('express')
const app = express()
const httpServer = require('http').createServer(app);
const tcp = require('./autoconnect.js');
const io = require('socket.io')(httpServer);
const io_wildcard = require('socketio-wildcard')();

io.use(io_wildcard);
app.use(express.static(__dirname + '/segway_ui/dist'));
app.use(express.static(__dirname + '/segway_ui/static'));

port = 3000;

/*Attendre la connection au serveur TCP*/
tcp.tryConnect('localhost', 1337,5000, function(client) {
    console.log('connection réussi')
    httpServer.listen(port)
})

/*Relancer les tentatives de connections lorsque le serveur est intérompue*/
tcp.event.on('close', ()=>{
  //TO DO - Emission d'une variable pour informé l'UI que l'on est déconnecté
  io.emit('disconnect');
  httpServer.close();
  
  tcp.tryConnect('localhost', 1337, 5000, function(client) {
    console.log('connection réussi')
    httpServer.listen(port)
    io.emit('connect')
  });
})

/*Reception des données sur le tcp*/
tcp.event.on('data', (data)=>{
  try{
    //console.log(data);
    io.emit('test', data);
  }catch (e){
    //console.log(data);
  }
  
})


/*Gestion du websocket du segway */
io.on('connection', (client)=>{
  console.log('user_connected');
  client.on('*', (raw)=>{
    console.log(raw.data)
    /*let jsonData = {};
    jsonData['topic'] = topic;
    jsonData['data'] = data;
    tcp.client.write(data);*/
  })
});

/* Routes */
app.get('/', (req, res)=> {
  res.sendFile('index.html')
})
