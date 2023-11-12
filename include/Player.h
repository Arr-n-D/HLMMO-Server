#pragma once
#include "game_messages.h"

//class NetworkManager;

class Player
{
	public: 
		Player(ENetPeer* peer);
		~Player();

		//void SendMessage(const char* message);
		void SendGameMessage(const char* data, size_t sizeOfMessage, GameMessage gMessage, bool isReliable);
		void SendRPC(const char* data, size_t sizeOfMessage);



	private:
		ENetPeer* peer;
};

