#include "TCPConnection.h"

#include <sys/socket.h>
#include <unistd.h>
#include <string>

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
        write(m_connection_descriptor, m_buffer.c_str(), m_buffer.size());
    }

    void TCPConnection::Accept(SocketPtr socket) {
        m_connection_descriptor = accept(socket->GetSocketDescriptor(), NULL, NULL);
    }

    void TCPConnection::Connect(SocketPtr socket) {
        m_connection_descriptor = connect(socket->GetSocketDescriptor(), )
    }
}