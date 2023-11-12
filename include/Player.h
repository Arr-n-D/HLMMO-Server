#pragma once
#include "game_messages.h"

class Player
{
	public: 
		Player();
		~Player();

		//void SendMessage(const char* message);
		void SendGameMessage(const char* data, size_t sizeOfMessage, GameMessage gMessage, bool isReliable);
		void SendRPC(const char* data, size_t sizeOfMessage);



	private:
		
};

