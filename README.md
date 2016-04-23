# network-media-player
Syncrhonize song choices to play on a set of speakers from multiple clients via a server based queue.

The idea is to allow multiple users, via a locally served mobile web app, to queue songs from YouTube,
Soundcloud, Spotify, etc. to play over a set of speakers. Also works if you just want an interface for
selecting music remotely.

Adding some more doucmentation soon, this project is currently undergoing a C rewrite. The new version
uses
- warmcat/libwebsockets to implement websocket server functionality (also investigating wslay)
- libuv for the handling of open connections
- mpv for streaming media content (also investigating ffmpeg, the library upon which mpv is based)
