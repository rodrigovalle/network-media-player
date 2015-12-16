#!/usr/bin/env python3
import sys
import pprint
import youtube_dl

pp = pprint.PrettyPrinter(indent=4);

with youtube_dl.YoutubeDL() as ydl:
    info = ydl.extract_info(sys.argv[1], download=False)
print(info['url'])
