#include <iostream>
#include <unistd.h>

#include "MPVController.h"
#include "songs.h"

using namespace std;

int main() {
    MPVController controller;

    cout << "playing watsky" << endl;
    controller.play(THE_ONE);
}
