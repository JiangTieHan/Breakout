#include <UdpSocket.h>
#include <logs.h>

#include <iostream>

#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <cerrno>

bool UdpSocket::bind(unsigned short port) {
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        std::cerr << "socket creation failed." << std::endl;
        return false;
    }

    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(port);
    if (bind(sockfd, (const struct sockaddr*)&addr, sizeof(addr)) < 0) {
        std::cerr << "socket bind failed." << std::endl;
        return false;
    }

    std::cout << "socket succesfully binded" << std::endl;
    return true;
}

void UdpSocket::send(const char* data, int len) {
    // Making the address here is temporary
    struct sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));

    addr.sin_family = AF_INET;
    addr.sin_port = sendPort;
    addr.sin_addr.s_addr = sendAddress;

    int flags = 0;
    int n = sendto(sockfd, data, len, flags, (const struct sockaddr*)&addr, sizeof(addr));
    if (n == -1) {
        std::cerr << "sendto() returned error" << std::endl;
    }
    else {
        std::cout << "Message sent." << std::endl;
    }
}

int UdpSocket::receive(char* data, int max_len) {
    int flags = MSG_DONTWAIT;
    int n = recvfrom(sockfd, data, max_len, flags, NULL, 0);

    if (n < 0) {
        if (errno != EWOULDBLOCK || errno != EAGAIN) {
            std::cerr << "recvfrom() returned error" << std::endl;
        }
        return 0;
    }
    else {
        std::cout << "Message received" << std::endl;
        return n;
    }
}

void UdpSocket::setSendAddress(uint32_t addr, uint16_t port) {
    sendAddress = htonl(addr);
    sendPort = htons(port);
}