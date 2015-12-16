#include <node.h>
#include <iostream>
#include <stdio.h>
#include "client.h"

using namespace v8;

/* So we're just gonna try implementing the play function
 * things that need to happen:
 *  - mpv handle needs to be created and its pointer stored [mpv_create()]
 *  - mpv settings gotta be set [mpv_set_option_string(context, option, arg)]
 *  - mpv gotta be initialized [mpv_initialize(context)]
 *
 *  - gotta issue play command to mpv [mvp_command(context, command)]
 *      const char* cmd[] = {"loadfile", *url, NULL};
 *      check_error(mpv_command(context, cmd));
 *
 *  - gotta wait until the song is finished playing and issue a callback
 *      while(1) {
 *        mpv_event* event = mpv_wait_event(context, 10000);
 *        if(event->event_id == MPV_EVENT_END_FILE) {
 *          // do stuff
 *        }
 *      }
 *
 *  - gotta kill mpv [mpv_terminate_destroy(context)]
 *
 *  EXTRA: mpv options
 *  cache         yes
 *  cache-secs    5
 *  cache-initial 0
 *  no-video
 */

// HELPER FUNCTIONS
/**
 * Takes an mpv error code and prints a corresponding error message to stdout.
 */
static inline void check_error(int status)
{
    if(status < 0) {
        std::cout << "mpv API error: " << mpv_error_string(status) << std::endl;
    }
}

/**
 * Removes carriage returns from the end of v8::String::Utf8 objects if present.
 * Input urls for mpv cannot end in carriage returns.
 */
static char* remove_return(String::Utf8Value& s)
{
    char* t = *s;  // temporary string

    char* q = t + (s.length() - 1);
    if(*q == '\n' || *q == '\r') {
        *q = '\0';
    }

    return t;
}

// JAVASCRIPT BINDINGS
mpv_handle* ctx = nullptr;

void mpvInit(const FunctionCallbackInfo<Value>& args)
{
    Isolate* isolate = Isolate::GetCurrent();
    HandleScope scope(isolate);

    ctx = mpv_create();
    mpv_set_option_string(ctx, "no-video", "");
    mpv_initialize(ctx);
}

void mpvPlay(const FunctionCallbackInfo<Value>& args)
{
    Isolate* isolate = Isolate::GetCurrent();
    HandleScope scope(isolate);

    String::Utf8Value utf8_url(args[0]);
    const char* cmd[] = {"loadfile", remove_return(utf8_url), NULL};

    mpv_command_async(ctx, 0, cmd);
}

void mpvPause(const FunctionCallbackInfo<Value>& args)
{
    Isolate* isolate = Isolate::GetCurrent();
    HandleScope scope(isolate);

    mpv_set_property_string(ctx, "pause", "yes");
}

void mpvUnpause(const FunctionCallbackInfo<Value>& args)
{
    Isolate* isolate = Isolate::GetCurrent();
    HandleScope scope(isolate);

    mpv_set_property_string(ctx, "pause", "no");
}

void mpvKill(const FunctionCallbackInfo<Value>& args)
{
    Isolate* isolate = Isolate::GetCurrent();
    HandleScope scope(isolate);

    if(ctx) {
        mpv_terminate_destroy(ctx);
        ctx = nullptr;
    }
}

void InitAll(Handle<Object> exports)
{
    NODE_SET_METHOD(exports, "init", mpvInit);
    NODE_SET_METHOD(exports, "play", mpvPlay);
    NODE_SET_METHOD(exports, "pause", mpvPause);
    NODE_SET_METHOD(exports, "unpause", mpvUnpause);
    NODE_SET_METHOD(exports, "kill", mpvKill);
}

NODE_MODULE(node_mpv, InitAll)

