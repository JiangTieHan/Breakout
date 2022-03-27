#pragma once

class UdpSocket
{
public:
	bool bind(unsigned short port);
	void send(const char* data, int len);
	int receive(char* data, int max_len);

	void setSendAddress(uint32_t addr, uint16_t port);

private:
	int sockfd;
	uint32_t sendAddress;
	uint16_t sendPort;
};