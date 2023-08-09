#pragma once
#include "enet.h"

class NetworkManager {
	public:
		NetworkManager();
		~NetworkManager();

		void OnUpdate();
		void Initialize();

	private:
		void OnEvent(ENetEvent event);
		void OnMessagedReceived(ENetEvent event);
		//void HandleMessage(ENetEvent event);
		//void OnMessagedReceived(ENetEvent event);
		//void OnConnect(ENetEvent event);
		int InitializeEnet();
		ENetHost* server;
		bool serverInitialized = false;
};

