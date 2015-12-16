#include <iostream>
#include <string>
#include "client.h"
#include "MPVController.h"

using namespace std;

static inline void check_error(int status)
{
    if(status < 0) {
        cout << "mpv API error: " << mpv_error_string(status) << endl;
        exit(1);
    }
}

MPVController::MPVController()
{
    context = mpv_create();

    // load config files and stuff mpv_load_config_file() or mpv_set_option()
    check_error(mpv_set_option_string(context, "cache", "yes"));
    // check_error(mpv_set_option_string(context, "cache-default", "1024"));
    check_error(mpv_set_option_string(context, "cache-secs", "5"));
    check_error(mpv_set_option_string(context, "cache-initial", "0"));
    check_error(mpv_set_option_string(context, "no-video", ""));

    check_error(mpv_initialize(context));
}

MPVController::~MPVController()
{
    mpv_terminate_destroy(context);
}

void MPVController::play(string url)
{
    const char* cmd[] = {"loadfile", url.c_str(), NULL};
    mpv_command(context, cmd);
    while(1) {
        mpv_event* event = mpv_wait_event(context, 10000);
        if(event->event_id == MPV_EVENT_END_FILE) {
	    cout << mpv_event_name(event->event_id) << endl;
            return;
        }
    }
}

void MPVController::pause()
{
    mpv_set_property_string(context, "pause", "yes");
    // mpv_set_property_async doesn't work for some reason (?)
}

void MPVController::unpause()
{
    mpv_set_property_string(context, "pause", "no");
}

void MPVController::seek(string percent)
{
    const char* cmd[] = {"seek", percent.c_str(),
                         "absolute-percent+keyframes", NULL};
    mpv_command_async(context, 0, cmd);
}

void MPVController::setVolume(string percent)
{
    // TODO: not implemented
    // set the volume property
    return;
}

