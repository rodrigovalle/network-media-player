#ifndef MPVCONTROLLER_H
#define MPVCONTROLLER_H

#include <string>
#include "client.h"

class MPVController {
  private:
    mpv_handle* context;

  public:
    MPVController();
    ~MPVController();

    // These functions all issue asynchronous calls to the mpv api
    void play(std::string url);
    void pause();
    void unpause();
    void seek(std::string percent);
    void setVolume(std::string percent);
};

#endif
