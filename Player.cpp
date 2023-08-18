#include "Player.h"
//#include "NetworkManager.h"

Player::Player(ENetPeer* peer, NetworkManager* networkManager)
{
	this->peer = peer;
	this->networkManager = networkManager;
}

Player::~Player()
{
}
