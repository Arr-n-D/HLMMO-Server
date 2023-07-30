#include "enet.h"

#include <iostream>
#include <chrono>
#include <thread>
#include "msgpack.hpp"
#include <iomanip>
#include "sentry.h"
#include "Core/Core.h"

using ArrND::Core::Core;

const int TICKS_PER_SECOND = 20;

struct PlayerMove {
	float x;
	float y;
	float z;
    MSGPACK_DEFINE(x, y, z);
};

int OnUpdate() {

}


int main()
{
    

    int tickDurationMs = 1000 / TICKS_PER_SECOND;
    
    // Initialize our Core
    Core coreInstance = Core();
    coreInstance.init();

        // Main loop
    while (true) {
        // Get the start time for this tick
        auto tickStart = std::chrono::high_resolution_clock::now();

        // Call the update function
        int updateResult = OnUpdate(server);

        // Check if the update function returned a non-zero value (indicating an error)
        if (updateResult != 0) {
            std::cerr << "Error occurred during update. Exiting..." << std::endl;
            break;
        }

        // Calculate how much time has elapsed during this tick
        auto tickEnd = std::chrono::high_resolution_clock::now();
        auto tickDuration = std::chrono::duration_cast<std::chrono::milliseconds>(tickEnd - tickStart).count();

        // Calculate the amount of time we need to sleep to achieve the desired TPS
        int sleepTimeMs = tickDurationMs - tickDuration;
        //print sleep time 
        if (sleepTimeMs > 0) {
            std::this_thread::sleep_for(std::chrono::milliseconds(sleepTimeMs));
        }
    }

    }
    
    sentry_close();
    return 0;
}

