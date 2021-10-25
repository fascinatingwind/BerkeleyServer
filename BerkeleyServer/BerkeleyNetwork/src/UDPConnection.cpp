#include "UDPConnection.h"

#include <iostream>
#include <netdb.h>

namespace Network {
    UDPConnection::~UDPConnection() noexcept {
        m_sockaddr = nullptr;
    }

    std::string UDPConnection::GetBuffer() {
        return m_buffer;
    }

    void UDPConnection::Read() {
        if (m_sock_fd < 0) {
            return;
        }

        const size_t buffer_size = 1024;
        m_buffer.clear();
        char buffer[buffer_size + 1];
        const auto bytes = recvfrom(m_sock_fd, buffer, buffer_size, 0, m_sockaddr->ai_addr, & m_sockaddr->ai_addrlen);
        if (bytes < 0) {
            std::cerr << "UDP connection read failed." << std::endl;
            return;
        }

        buffer[bytes] = '\0';
        m_buffer.append(buffer);
    }

    void UDPConnection::Write() {
        if (m_sock_fd < 0)
            return;

        const auto bytes = sendto(m_sock_fd, m_buffer.c_str(), m_buffer.size(),
                                  0, m_sockaddr->ai_addr, m_sockaddr->ai_addrlen);
        if (bytes < 0)
            std::cerr << "UDP connection write failed" << std::endl;

    }

    void UDPConnection::Connect(SocketPtr socket) {
        m_sock_fd = socket->GetSock();
        m_sockaddr = socket->GetAddrInfo();
        m_is_connected = m_sock_fd > 0;
    }

    void UDPConnection::Accept(SocketPtr socket) {
        Connect(socket);
    }
}