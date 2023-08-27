#pragma once
#include "enet.h"
#include "Player.h"
#include <map>

class NetworkManager {
	public:
		NetworkManager();
		~NetworkManager();

		void OnUpdate();
		void Initialize();

		std::map<int, Player> connectedPlayers;

	private:
		ENetHost* server;
		bool serverInitialized = false;
		int InitializeEnet();
		void OnEvent(ENetEvent event);
		void OnMessagedReceived(ENetEvent event);
		//void HandleMessage(ENetEvent event);

		void OnClientConnect(ENetEvent event);
		void OnClientDisconnect(ENetEvent event);

		


};

