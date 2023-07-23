#include "enet.h"

#include <iostream>
#include <chrono>
#include <thread>

const int TICKS_PER_SECOND = 20;

struct PlayerPos {
	float x;
	float y;
	float z;
};

int OnUpdate(ENetHost* server) {

    ENetEvent event;

    while (enet_host_service(server, &event, 0))
    {
        std::cout << "enet_host_service" << std::endl;
        switch (event.type)
        {
        case ENET_EVENT_TYPE_CONNECT:
            printf("A new client connected from %x:%u.\n",
                event.peer->address.host,
                event.peer->address.port);
            /* Store any relevant client information here. */
            //event.peer->data = "Client information";
            break;
        case ENET_EVENT_TYPE_RECEIVE:
            //cast packet data to struct PlayerPos
            //PlayerPos* playerPos = 
            printf("A packet of length %u containing %s was received from %s on channel %u.\n",
                event.packet->dataLength,
                (PlayerPos*)event.packet->data,
                event.peer->data,
                event.channelID);
            /* Clean up the packet now that we're done using it. */
            enet_packet_destroy(event.packet);

            break;

        case ENET_EVENT_TYPE_DISCONNECT:
            printf("%s disconnected.\n", event.peer->data);
            /* Reset the peer's client information. */
            event.peer->data = NULL;
        }
    }

    return 0; // Return 0 to indicate successful update

}


int main()
{
    int tickDurationMs = 1000 / TICKS_PER_SECOND;


    if (enet_initialize() != 0)
    {
        fprintf(stderr, "An error occurred while initializing ENet.\n");
        return EXIT_FAILURE;
    }
    else {
        printf("ENet initialized.\n");

        ENetAddress address;
        ENetHost* server;
        /* Bind the server to the default localhost.     */
        /* A specific host address can be specified by   */
        /* enet_address_set_host (& address, "x.x.x.x"); */
        //address.host = ENET_HOST_ANY;
        /* Bind the server to port 1234. */
        enet_address_set_host(&address, "localhost");
        address.port = 9500;
        server = enet_host_create(&address /* the address to bind the server host to */,
            32      /* allow up to 32 clients and/or outgoing connections */,
            2      /* allow up to 2 channels to be used, 0 and 1 */,
            0      /* assume any amount of incoming bandwidth */,
            0      /* assume any amount of outgoing bandwidth */);

        if (server == NULL)
        {
            fprintf(stderr,
                "An error occurred while trying to create an ENet server host.\n");
            exit(EXIT_FAILURE);
        }

       
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
    
    return 0;
}

