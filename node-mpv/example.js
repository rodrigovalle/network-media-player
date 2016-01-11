var mpv = require('./build/Release/node-mpv');
var video_id = 'Fx8pS_sOi-A';

process.stdin.resume();
mpv.init();

var spawn = require('child_process').spawn;
var yt_link = spawn('./yt_link.py ');

console.log("yt_link online");

yt_link.stdin.write(video_id);
yt_link.stdout.on('readable', function() {
    var videoURL = stdout.read();
    mpv.play(videoURL);
});

process.on('exit', function() {
    console.log('term signal recieved');
    mpv.kill();
    process.exit();
});

