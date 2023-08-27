#pragma once
#include "enet.h"
#include "Player.h"
#include <map>
#include <openssl/ssl.h>
#include <openssl/err.h>

class NetworkManager {
	public:
		NetworkManager();
		~NetworkManager();

		void OnUpdate();
		void Initialize();

		// Getter function for our ctx
		SSL_CTX* GetCtx();

		std::map<int, Player> connectedPlayers;

	private:
		ENetHost* server;

		SSL_CTX* ctx = SSL_CTX_new(DTLS_method());

		bool serverInitialized = false;

		int InitializeEnet();

		void OnEvent(ENetEvent event);
		void OnMessagedReceived(ENetEvent event);
		//void HandleMessage(ENetEvent event);

		void OnClientConnect(ENetEvent event);
		void OnClientDisconnect(ENetEvent event);

		


};

