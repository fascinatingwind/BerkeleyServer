#include "TCPSocket.h"

#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <iostream>

namespace Network {
    TCPSocket::TCPSocket(const std::string &port, const std::string &address) {
        auto *info = InitAddrInfo();
        addrinfo *servinfo;
        info->ai_socktype = SOCK_STREAM;
        if (auto rv = getaddrinfo(address.empty() ? nullptr : address.c_str(), port.c_str(), info, &servinfo); rv != 0) {
            std::cerr << "getadrinfo :" << gai_strerror(rv) << std::endl;
        }

        for(auto* p = servinfo; p != nullptr; p = p->ai_next)
        {
            if (m_socket = socket(p->ai_family, p->ai_socktype, p->ai_protocol); m_socket == -1) {
                std::cerr << "Socket not created.";
                continue;
            }
            m_sockaddr = p;
            break;
        }
    }
}