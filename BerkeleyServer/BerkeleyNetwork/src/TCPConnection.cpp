#include "TCPConnection.h"

#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string>
#include <iostream>
#include <arpa/inet.h>

namespace Network {
    void *get_in_addr(struct sockaddr *sa) {
        if (sa->sa_family == AF_INET) {
            return &(((struct sockaddr_in *) sa)->sin_addr);
        }
        return &(((struct sockaddr_in6 *) sa)->sin6_addr);
    }

    TCPConnection::~TCPConnection() {
        if (m_socket_descriptor > 0)
            close(m_socket_descriptor);
    }

    std::string TCPConnection::GetBuffer() {
        return m_buffer;
    }

    void TCPConnection::ReadAsync() {

    }

    void TCPConnection::WriteAsync() {

    }

    void TCPConnection::Read() {
        const auto buffer_size = ReceiveBufferSize();
        m_buffer.clear();
        char buffer[buffer_size + 1];
        auto receive = recv(m_socket_descriptor, &buffer, buffer_size, MSG_NOSIGNAL);
        if (receive > 0) {
            buffer[receive] = '\0';
            m_buffer.append(buffer);
        }
    }

    void TCPConnection::Write() {
        SendBufferSize();
        auto result = send(m_socket_descriptor, m_buffer.c_str(), m_buffer.size(), MSG_NOSIGNAL);
        if (result < 0)
            std::cerr << "Write result :" << result << std::endl;
    }

    void TCPConnection::Accept(const Socket &socket) {
        if (!socket.IsValid()) {
            std::cerr << "Socket invalid. Accept failed" << std::endl;
            return;
        }
        socklen_t storage_size = sizeof m_remote_addr_storage;
        m_socket_descriptor = accept(socket.GetSocketDescriptor(), (struct sockaddr *) &m_remote_addr_storage,
                                     &storage_size);
        if (m_socket_descriptor < 0)
            std::cerr << "Accept error" << std::endl;
        size_t size = 32;
        char buffer[size];
        for (auto receive = recv(socket.GetSocketDescriptor(), &buffer, size, 0); receive > 0;
             receive = recv(socket.GetSocketDescriptor(), &buffer, size, 0)) {
            inet_ntop(m_remote_addr_storage.ss_family, get_in_addr((struct sockaddr *) &m_remote_addr_storage), buffer,
                      size);
            m_buffer.append(buffer);
        }
    }

    void TCPConnection::Connect(const Socket &socket) {
        if (!socket.IsValid()) {
            std::cerr << "Socket invalid. Connect failed" << std::endl;
            return;
        }

        auto *sa = socket.GetAddrInfo();
        if (!sa)
            return;
        m_socket_descriptor = socket.GetSocketDescriptor();
        const auto result = connect(m_socket_descriptor, sa->ai_addr, sa->ai_addrlen);
        if (result < 0)
            std::cerr << "Error connect to host." << std::endl;
    }

    void TCPConnection::SendBufferSize() {
        uint32_t buffer_size = m_buffer.size();
        buffer_size = htonl(buffer_size);
        auto result = send(m_socket_descriptor, &buffer_size, sizeof(uint32_t), MSG_NOSIGNAL);
        if (result < 0)
            std::cerr << "Send buffer size error:" << result << std::endl;
    }

    uint32_t TCPConnection::ReceiveBufferSize() {
        uint32_t buffer_size;
        auto result = recv(m_socket_descriptor, &buffer_size, sizeof(uint32_t), MSG_NOSIGNAL);
        if (result < 0)
            std::cerr << "Receive buffer size error" << std::endl;
        return ntohl(buffer_size);
    }
}