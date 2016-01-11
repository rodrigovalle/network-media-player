var WebSocketServer = require('ws').Server,
    wss = new WebSocketServer({port: 8080});

var mpv = require('node-mpv');
var exec = require('child_process').exec;

/* instead of getting video streams 1 at a time, modify yt_link
 * to idle in the background when not retrieving a link
 * this should keep the process creation overhead cost at a minimum
 */
function getPlayableURL(videoID, callback) {
    exec('./yt_link.py ' + videoID,
        function(error, stdout, stderr) {
            callback(stdout);
        }
    );
}

wss.broadcast = function broadcast(data) {
    wss.clients.forEach(function each(client) {
        client.send(data);
    });
};

wss.on('connection', function(ws) {
    console.log('new client connected');
    ws.on('message', function(videoID) {
        console.log('playing: ' + videoID);
        getPlayableURL(videoID, function(url) {
            console.log('should be playing music rn :/');
            mpv.play(url);
        });
    });
});


