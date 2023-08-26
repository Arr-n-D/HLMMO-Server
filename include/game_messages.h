#pragma once
#include <iostream>
#include "msgpack.hpp"

enum GameMessage {
	MOVE = 0,
	RPC = 1,
};

enum GameMessageReliability {
	UNRELIABLE = 0,
	RELIABLE = 1,
};

enum Channels {
	MOVE_CHANNEL = 0,
	RPC_CHANNEL = 1,
};

struct GameMessageMove {
	float x;
	float y;
	float z;
	MSGPACK_DEFINE(x, y, z);
};

struct Packet {
	int packetType;
	size_t sizeOfMessage;
	std::string data;
	MSGPACK_DEFINE(packetType, sizeOfMessage, data);
};

//create a list of GameMessage -> void handlers 
//std::map<GameMessage, void> gameMessageHandlers;