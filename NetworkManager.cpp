#include <iostream>
#include "msgpack.hpp"
#include "NetworkManager.h"



    NetworkManager::NetworkManager()
    {
    }

    NetworkManager::~NetworkManager()
    {
    }

    void NetworkManager::OnUpdate()
    {
        if (this->serverInitialized) {
            ENetEvent event;

            while (enet_host_service(this->server, &event, 0))
            {
                this->OnEvent(event);
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
			else {
				this->serverInitialized = true;
				printf("ENet server initialized.\n");
			}
        }
    }



    void NetworkManager::OnEvent(ENetEvent event)
    {
        std::cout << "enet_host_service" << std::endl;
        switch (event.type)
        {
            case ENET_EVENT_TYPE_CONNECT:
                printf("%s connected.\n", event.peer->data);
                //call on connect
            break;
            
            case ENET_EVENT_TYPE_RECEIVE:
                //call handle message received
                this->OnMessagedReceived(event);
           
            break;
            //msgpack::sbuffer buffer;

            case ENET_EVENT_TYPE_DISCONNECT:
                //call on disconnect
                printf("%s disconnected.\n", event.peer->data);
                /* Reset the peer's client information. */
                event.peer->data = NULL;
            break;
        }
    }

    void NetworkManager::OnMessagedReceived(ENetEvent event)
    {
        msgpack::object_handle oh = msgpack::unpack((const char*)event.packet->data, event.packet->dataLength);

        // deserialized object is valid during the msgpack::object_handle instance is alive.
        msgpack::object deserialized = oh.get();

 
        printf("A packet of length %u containing %s was received from %s on channel %u.\n",
            event.packet->dataLength,
            event.packet->data,
            event.peer->data,
            event.channelID);
        /* Clean up the packet now that we're done using it. */
        enet_packet_destroy(event.packet);

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


