###############################################################################
# Sets up a build environment for the song-queue app
# Dependencies:
#  -python3, pip3
#  -pafy
#  -git
#  -mpv
###############################################################################

FROM ubuntu:vivid

RUN apt-get -y update
RUN apt-get -y install build-essential git vim
RUN apt-get -y install python3-pip
RUN apt-get -y install mpv

# pafy
RUN pip3 install pafy

# home environment
RUN useradd dev
RUN mkdir /home/dev/ && chown -R dev: /home/dev

ADD song_queue.py /home/dev/song_queue.py
ADD mpv.py /home/dev/mpv.py

CMD /bin/bash
