var mpv = require('./build/Release/node-mpv');
var video_id = 'xTAW85ITHz8';

process.stdin.resume();

var exec = require('child_process').exec;
var yt_link = exec('./yt_link.py ' + video_id,
    function(error, stdout, stderr) {
        mpv.play(stdout);
    }
);

process.on('exit', function() {
    console.log('term signal recieved');
    mpv.kill();
    process.exit();
});

