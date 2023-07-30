#include "NetworkManager.h"
#include <iostream>

#pragma region Public methods
NetworkManager::NetworkManager()
{
}

NetworkManager::~NetworkManager()
{
}

void NetworkManager::OnUpdate()
{
    ENetEvent event;

    while (enet_host_service(this->server, &event, 0))
    {
        std::cout << "enet_host_service" << std::endl;
        switch (event.type)
        {
        case ENET_EVENT_TYPE_CONNECT:
            break;
        case ENET_EVENT_TYPE_RECEIVE:
        {
            msgpack::object_handle oh =
                msgpack::unpack((const char*)event.packet->data, event.packet->dataLength);

            // deserialized object is valid during the msgpack::object_handle instance is alive.
            msgpack::object deserialized = oh.get();

            auto v2 = deserialized.as<PlayerMove>();
            std::cout << std::setprecision(15) << v2.x << std::endl;
            std::cout << std::setprecision(15) << v2.y << std::endl;
            std::cout << std::setprecision(15) << v2.z << std::endl;

            //cast packet data to struct PlayerPos
            //PlayerPos* playerPos = 
            printf("A packet of length %u containing %s was received from %s on channel %u.\n",
                event.packet->dataLength,
                event.packet->data,
                event.peer->data,
                event.channelID);
            /* Clean up the packet now that we're done using it. */
            enet_packet_destroy(event.packet);

            break;
        }
        //msgpack::sbuffer buffer;


        case ENET_EVENT_TYPE_DISCONNECT:
            printf("%s disconnected.\n", event.peer->data);
            /* Reset the peer's client information. */
            event.peer->data = NULL;
        }
    }
}
void NetworkManager::Initialize()
{
    if (this->InitializeEnet() == EXIT_SUCCESS)
    {
        ENetAddress address;
       
        enet_address_set_host(&address, "localhost");
        address.port = 9500;
        this->server = enet_host_create(&address /* the address to bind the server host to */,
            32      /* allow up to 32 clients and/or outgoing connections */,
            2      /* allow up to 2 channels to be used, 0 and 1 */,
            0      /* assume any amount of incoming bandwidth */,
            0      /* assume any amount of outgoing bandwidth */);

        if (this->server == NULL)
        {
            fprintf(stderr,
                "An error occurred while trying to create an ENet server host.\n");
            //exit(EXIT_FAILURE);
        }
	}
}
#pragma endregion



#pragma region Private methods


void NetworkManager::OnEvent(ENetEvent event)
{
}

int NetworkManager::InitializeEnet()
{
    if (enet_initialize() != 0)
    {
        printf("An error occurred while initializing ENet.\n");
        return EXIT_FAILURE;
    }
    else {
        printf("ENet initialized.\n");
        return EXIT_SUCCESS;
    }

    return 1;
}

#pragma endregion
