#include "TCPConnection.h"

#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string>
#include <iostream>

namespace Network {

    TCPConnection::~TCPConnection() {
        if (m_connection_descriptor > 0)
            close(m_connection_descriptor);
    }

    std::string TCPConnection::GetBuffer() {
        return m_buffer;
    }

    void TCPConnection::ReadAsync() {

    }

    void TCPConnection::WriteAsync() {

    }

    void TCPConnection::Read() {
        size_t size = 32;
        char buffer[size];
        while (read(m_connection_descriptor, buffer, size)) {
            m_buffer.append(buffer);
        };
    }

    void TCPConnection::Write() {
        const auto result = write(m_connection_descriptor, m_buffer.c_str(), m_buffer.size());
        std::cerr << "Write result :" << result << std::endl;
    }

    void TCPConnection::Accept(SocketPtr socket) {
        m_connection_descriptor = accept(socket->GetSocketDescriptor(), NULL, NULL);
        LogIfError("Accept socket failed");
    }

    void TCPConnection::Connect(SocketPtr socket) {
        const auto* sa = socket->GetSockAddr();
        if(sa == nullptr)
            return;
        m_connection_descriptor = connect(socket->GetSocketDescriptor(), (struct sockaddr *)sa, sizeof *sa);
        LogIfError("Connect to socket failed");
    }

    void TCPConnection::LogIfError(const std::string& message) const {
        if(m_connection_descriptor < 1)
        {
            std::cerr << message << " : " << m_connection_descriptor << std::endl;
        }
    }
}