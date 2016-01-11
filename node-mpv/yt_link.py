#!/usr/bin/env python3
import sys
import selectors
import youtube_dl

# ytdl stuff, youtube_dl handles url calculation/requests
ytdl_opts = {
    'quiet': True
}

def getURL(videoID):
    with youtube_dl.YoutubeDL(ytdl_opts) as ydl:
        info = ydl.extract_info(videoID, download=False)
    return info['url']

# the idea is to keep this python process idle until we ask
# it to go fetch us more youtube URLs
# we do this using the selectors python 3.x module, which
# gives similar functionality to the *nix select() function
stdinSel = selectors.DefaultSelector()
stdinSel.register(sys.stdin, selectors.EVENT_READ)

# main loop
while True:
    events = stdinSel.select() # wake us up when stdin has something
    for key, mask in events:
        videoID = key.fileobj.readline() # read line from stdin
        print(getURL(videoID))

