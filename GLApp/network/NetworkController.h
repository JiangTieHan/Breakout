#pragma once

#include "UdpSocket.h"

class NetworkController
{
public:
	enum NetworkState
	{
		WAITING, POLLING
	};

	void Init();
	void Update();

private:
	UdpSocket socket;
};