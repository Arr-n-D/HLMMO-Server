#pragma once
#include "Player.h"
#include <map>
#include <steam/steamnetworkingsockets.h>
#include <steam/isteamnetworkingutils.h>
#ifndef STEAMNETWORKINGSOCKETS_OPENSOURCE
	#include <steam/steam_api.h>
#endif


class NetworkManager {
	public:
		NetworkManager();
		~NetworkManager();

		void OnUpdate();
		void Initialize();

		std::map<int, Player> m_ConnectedPlayers;

		SteamNetworkingMicroseconds  m_LogTimeZero;

	private:
		

		bool m_ServerInitialized = false;

		int InitializeNetworkingLibrary();

		void OnEvent();
		void OnMessagedReceived();
		//void HandleMessage(ENetEvent event);

		void OnClientConnect();
		void OnClientDisconnect();

		


};

