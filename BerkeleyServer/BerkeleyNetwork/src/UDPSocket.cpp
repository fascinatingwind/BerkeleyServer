#include "UDPSocket.h"

#include <sys/socket.h>
#include <iostream>

namespace Network {
    UDPSocket::UDPSocket(const std::string& port, const std::string &address) {
        addrinfo info = {};
        info.ai_family = AF_INET;
        info.ai_socktype = SOCK_DGRAM;
        if (address.empty()) {
            info.ai_flags = AI_PASSIVE;
        }

        // m_sockaddr set here
        if (auto rv = getaddrinfo(address.empty() ? nullptr : address.c_str(), port.c_str(), &info, &m_sockaddr);
                rv != 0) {
            std::cerr << "getadrinfo :" << gai_strerror(rv) << std::endl;
        }
    }
}