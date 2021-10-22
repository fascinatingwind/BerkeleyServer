#include "Socket.h"

#include <sys/socket.h>
#include <iostream>
#include <netdb.h>

namespace Network {
    Socket::~Socket() {
        freeaddrinfo(m_sockaddr);
        shutdown(m_sock_fd, SHUT_RDWR);
    }

    bool Socket::IsValid() const {
        return m_sock_fd > 0;
    }

    addrinfo *Socket::GetAddrInfo() const {
        return m_sockaddr;
    }

    void Socket::Bind() {
        if (IsValid() && m_sockaddr != nullptr) {
            int result = bind(m_sock_fd, m_sockaddr->ai_addr, m_sockaddr->ai_addrlen);
            if (result < 0)
                std::cerr << "Socket bind error" << std::endl;
        }
    }

    void Socket::Listen() const {
        if (IsValid()) {
            listen(m_sock_fd, 10);
        }
    }

   void Socket::SetSockOpt() {
        if (IsValid()) {
            int yes = 1;

            if (setsockopt(m_sock_fd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1) {
                std::cerr << "Set sockopt error" << std::endl;
            }
        }
    }

    void Socket::CreateSocket() {
        if (IsValid())
            shutdown(m_sock_fd, SHUT_RDWR);

        m_sock_fd = socket(m_sockaddr->ai_family, m_sockaddr->ai_socktype, m_sockaddr->ai_protocol);
        if (!IsValid()) {
            std::cerr << "Create socket error." << std::endl;
        }
    }
}
