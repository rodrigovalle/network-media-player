var WebSocketServer = require('ws').Server;
var wss = new WebSocketServer({ port: 8080 });
console.log('started websocket server');

wss.on('connection', function(ws) {
    console.log('connection established');

    ws.on('message', function(message) {
         console.log('received: %s', message);
         ws.send(message);
    });
});

