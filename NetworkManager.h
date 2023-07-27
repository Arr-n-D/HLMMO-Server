#pragma once
#pragma once
#include "enet.h"

class NetworkManager
{
	public:
	NetworkManager();
	~NetworkManager();

	void OnUpdate();

	private:
		void OnMessagedReceived(ENetEvent event);
		void OnConnect(ENetEvent event);
};

