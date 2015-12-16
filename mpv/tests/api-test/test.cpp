#include <cstdlib>
#include <iostream>
#include "client.h"

using namespace std;

static inline void check_error(int status)
{
    if (status < 0) {
        cout << ":( - mpv API error: " << mpv_error_string(status) << endl;
        exit(1);
    }
}
        
int main(int argc, char* argv[]) {
    mpv_handle* ctx = mpv_create();
    if (!ctx) {
        cout << ":( - couldn't create an mpv context" << endl;
    }
    
    // put in some config stuff
    // use mpv_set_option() or mpv_load_config_file()
    mpv_set_option_string(ctx, "no-video", "");

    check_error(mpv_initialize(ctx));

    const char* cmd[] = {"loadfile", argv[1], NULL};
    cout << argv[1] << endl;
    check_error(mpv_command_async(ctx, 0, cmd));

    while (1) {
        mpv_event* event = mpv_wait_event(ctx, 10000);
        cout << "event: " << mpv_event_name(event->event_id) << endl;
        if(event->event_id == MPV_EVENT_SHUTDOWN) {
            break;
        }
    }
    mpv_terminate_destroy(ctx);
    return 0;
}


