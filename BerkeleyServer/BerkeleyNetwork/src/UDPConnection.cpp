#include "UDPConnection.h"
#include <iostream>

namespace Network {
    UDPConnection::~UDPConnection() noexcept {
        if (m_socket_descriptor > 0)
            shutdown(m_socket_descriptor, SHUT_RDWR);

        m_sockaddr = nullptr;
    }

    std::string UDPConnection::GetBuffer() {
        return m_buffer;
    }

    void UDPConnection::Read() {
        if (m_socket_descriptor < 0) {
            return;
        }

        const size_t buffer_size = 1024;
        m_buffer.clear();
        char buffer[buffer_size + 1];
        socklen_t addr_len = sizeof m_remote_addr_storage;
        const auto bytes = recvfrom(m_socket_descriptor, buffer, buffer_size, 0,
                                    (struct sockaddr *) &m_remote_addr_storage, &addr_len);
        if (bytes < 0) {
            std::cerr << "UDP connection read failed." << std::endl;
            return;
        }

        buffer[bytes] = '\0';
        m_buffer.append(buffer);
    }

    void UDPConnection::Write() {
        if (m_socket_descriptor < 0)
            return;

        const auto bytes = sendto(m_socket_descriptor, m_buffer.c_str(), m_buffer.size(),
                                  0, m_sockaddr->ai_addr, m_sockaddr->ai_addrlen);
        if (bytes < 0)
            std::cerr << "UDP connection write failed" << std::endl;

    }

    void UDPConnection::Connect(const Socket &socket) {
        m_socket_descriptor = socket.GetSocketDescriptor();
        m_sockaddr = socket.GetAddrInfo();
    }

    void UDPConnection::Accept(const Socket &socket) {
        m_socket_descriptor = socket.GetSocketDescriptor();
        m_sockaddr = socket.GetAddrInfo();
    }

    void UDPConnection::WriteAsync() {

    }

    void UDPConnection::ReadAsync() {

    }
}