#include "TCPSocket.h"

#include <sys/socket.h>
#include <unistd.h>
#include <iostream>

namespace Network {
    TCPSocket::TCPSocket(const std::string &port, const std::string &address) {
        addrinfo info = {};
        info.ai_family = AF_INET;
        info.ai_socktype = SOCK_STREAM;
        if(address.empty())
        {
            info.ai_flags = AI_PASSIVE;
        }

        // m_sockaddr set here
        if (auto rv = getaddrinfo(address.empty() ? nullptr : address.c_str(), port.c_str(), &info, &m_sockaddr);
                rv != 0) {
            std::cerr << "getadrinfo :" << gai_strerror(rv) << std::endl;
        }
    }

    TCPSocket::~TCPSocket() noexcept {
        freeaddrinfo(m_sockaddr);
        shutdown(m_socket, SHUT_RDWR);
    }

    void TCPSocket::CreateSocket() {
        if (IsValid())
            close(m_socket);

        m_socket = socket(m_sockaddr->ai_family, m_sockaddr->ai_socktype, m_sockaddr->ai_protocol);
        if (!IsValid()) {
            std::cerr << "Create socket error." << std::endl;
        }
    }

    void TCPSocket::Bind() {
        if (IsValid() && m_sockaddr != nullptr) {
            int result = bind(m_socket, m_sockaddr->ai_addr, m_sockaddr->ai_addrlen);
            if (result < 0)
                std::cerr << "Socket bind error" << std::endl;
        }
    }

    void TCPSocket::Listen() const {
        if (IsValid()) {
            listen(m_socket, 10);
        }
    }

    void TCPSocket::SetSockOpt() {
        if (IsValid()) {
            int yes = 1;

            if (setsockopt(m_socket, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1) {
                std::cerr << "Set sockopt error" << std::endl;
            }
        }
    }

    bool TCPSocket::IsValid() const {
        return m_socket > 0;
    }

    int TCPSocket::GetSocketDescriptor() const {
        return m_socket;
    }

    addrinfo *TCPSocket::GetAddrInfo() const {
        return m_sockaddr;
    }
}