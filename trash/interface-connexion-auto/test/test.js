const fs = require('fs');
const net = require('net');
const log = require('log-to-file');

log('[Démarage du test]')

const server = net.createServer(function(socket) {
    console.log('Interface Graphique Connecté')
    let sendMess = setInterval(()=>{
        log('[Donnée envoyée]')
        test_val = fs.readFileSync('test.json', 'utf8'); // Lecture du JSON
        socket.write(test_val); // Envoie du JSON à travers le TCP
    }, 1000)
    
    socket.on('data', (data) => {
        log('[Donnée reçu] '+JSON.parse(data));
        console.log(JSON.parse(data)); // Affiche les données reçu
    })

    socket.on('close', () => {
        log('[Fin test]')
        clearInterval(sendMess);
    })

});


console.log("Test lancé");
console.log("En attente d'une connection au serveur tcp");



server.listen(1337, '127.0.0.1');