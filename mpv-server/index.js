var WebSocketServer = require('ws').Server,
    wss = new WebSocketServer({port: 8080});

var mpv = require('node-mpv');
var exec = require('child_process').exec;

wss.on('connection', function(ws) {
    ws.on('message', function(videoID) {
        console.log('playing: ' + videoID);
        getPlayableURL(videoID, function(url) {
            mpv.play(url);
        });
    });
});

function getPlayableURL(videoID, callback) {
    exec('./yt_link.py ' + videoID,
        function(error, stdout, stderr) {
            callback(stdout);
        }
    );
}

