#!/usr/bin/env python3
import sys
import youtube_dl

ytdl_opts = {
    'quiet': True
}
with youtube_dl.YoutubeDL(ytdl_opts) as ydl:
    info = ydl.extract_info(sys.argv[1], download=False)
print(info['url'])
