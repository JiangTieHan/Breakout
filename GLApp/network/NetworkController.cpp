#include "NetworkController.h"

#include <iostream>

#define BIND_PORT 24240

void NetworkController::Init()
{
	std::cout << "HERE" << std::endl;
	socket.bind(BIND_PORT);
}

void NetworkController::Update()
{
	// State machine
	// Send and receive messages
}