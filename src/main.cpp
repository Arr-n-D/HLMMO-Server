#include <chrono>
#include <thread>
#include "Core.h"

const int TICKS_PER_SECOND = 20;

int main()
{
    
    int tickDurationMs = 1000 / TICKS_PER_SECOND;
    
    // Initialize our Core
    Core coreInstance = Core();
    coreInstance.Initialize();

        // Main loop
    while (true) {
        // Get the start time for this tick
        auto tickStart = std::chrono::high_resolution_clock::now();

        coreInstance.GetNetworkManager().OnUpdate();

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
    
    sentry_close();
    return 0;
}

