#pragma once
#include "enet.h"

class NetworkManager;

class Player
{
	public: 
		Player(ENetPeer* peer, NetworkManager* networkManager);
		~Player();

		//void SendMessage(const char* message);



	private:
		NetworkManager* networkManager;
		ENetPeer* peer;
};

