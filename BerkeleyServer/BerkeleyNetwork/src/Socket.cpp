#include "Socket.h"

#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <iostream>

namespace Network {
    Socket::~Socket() {
        freeaddrinfo(m_sockaddr);
        close(m_socket);
    }

    addrinfo *Socket::InitAddrInfo() {
        auto sa = new addrinfo;
        sa->ai_family = AF_INET;
        sa->ai_flags = AI_PASSIVE;
        return sa;
    }

    bool Socket::IsValid() const {
        return m_socket != -1;
    }

    int Socket::GetSocketDescriptor() const {
        return m_socket;
    }

    addrinfo *Socket::GetAddrInfo() const {
        return m_sockaddr;
    }

    void Socket::Bind() {
        if (m_socket && m_sockaddr) {
            int result = bind(m_socket, m_sockaddr->ai_addr, m_sockaddr->ai_addrlen);
            if (result < 0)
                std::cerr << "Socket bind error" << std::endl;
        }
    }

    void Socket::Listen() const {
        if (m_socket) {
            listen(m_socket, 10);
        }
    }

    void Socket::SetSockOpt() {
        if (m_socket) {
            int yes = 1;

            if (setsockopt(m_socket, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1) {
                std::cerr << "Set sockopt error" << std::endl;
            }
        }
    }
}
}