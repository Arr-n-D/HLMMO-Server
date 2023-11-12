#include <iostream>
#include "msgpack.hpp"
#include "NetworkManager.h"
#include "game_messages.h"

NetworkManager::NetworkManager()
{
    printf("NetworkManager created.\n");
}

NetworkManager::~NetworkManager()
{
}

void NetworkManager::OnUpdate()
{
    if (this->m_ServerInitialized) {
        // ENetEvent event;

        // while (enet_host_service(this->server, &event, 0))
        // {
        //     this->OnEvent(event);
        // }
    }
}

void NetworkManager::Initialize()
{
    if (this->InitializeNetworkingLibrary() == EXIT_SUCCESS) {
        // ENetAddress address;

        // enet_address_set_host(&address, "localhost");
        // address.port = 9500;
        // this->server = enet_host_create(&address /* the address to bind the server host to */,
        //                                 32 /* allow up to 32 clients and/or outgoing connections */,
        //                                 2 /* allow up to 2 channels to be used, 0 and 1 */,
        //                                 0 /* assume any amount of incoming bandwidth */,
        //                                 0 /* assume any amount of outgoing bandwidth */);

        // if (this->server == NULL) {
        //     fprintf(stderr,
        //             "An error occurred while trying to create an ENet server host.\n");
        //     exit(EXIT_FAILURE);
        // }
        // else {
        //     this->serverInitialized = true;
        //     printf("Network server initialized.\n");
        // }
    }
}

void NetworkManager::OnEvent()
{

}

void NetworkManager::OnMessagedReceived()
{
    // msgpack::object_handle oh = msgpack::unpack((const char *)event.packet->data, event.packet->dataLength);
    // // deserialized object is valid during the msgpack::object_handle instance is alive.
    // msgpack::object deserialized = oh.get();

    // // deserialized should be of type Packet
    // Packet packet = deserialized.as<Packet>();

    // std::cout << "packetType: " << packet.packetType << std::endl;
    // std::cout << "sizeOfMessage: " << packet.sizeOfMessage << std::endl;

    // printf("A packet of length %u containing %s was received from %s on channel %u.\n",
    //        event.packet->dataLength,
    //        event.packet->data,
    //        event.peer->data,
    //        event.channelID);
    // /* Clean up the packet now that we're done using it. */
  
}

void NetworkManager::OnClientConnect()
{
    // printf("Client connected with peer id: %s connected.\n", event.peer->incomingPeerID);

    // // connectedPlayers.insert(std::pair<int, Player>(event.peer->incomingPeerID, Player(event.peer, this)));

    // // //print all the peer ids
    // // for (auto const& x : connectedPlayers)
    // // {
    // // 	std::cout << x.first << std::endl;
    // // }
}

int NetworkManager::InitializeNetworkingLibrary()
{
    SteamDatagramErrMsg errMsg;

    if (!GameNetworkingSockets_Init(nullptr, errMsg)) {
        printf("GameNetworkingSockets_Init failed.  %s", errMsg);
        return EXIT_FAILURE;
    }
    else {
        printf("GameNetworkingSockets_Init successful.\n");
        this->m_LogTimeZero = SteamNetworkingUtils()->GetLocalTimestamp();
        return EXIT_SUCCESS;
    }

    return 1;
}