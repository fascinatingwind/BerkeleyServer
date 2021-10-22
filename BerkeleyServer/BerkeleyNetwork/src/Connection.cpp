#include "Connection.h"

namespace Network {
    bool Connection::IsConnected() const {
        return m_is_connected;
    }

    void Connection::SetBuffer(std::string message) {
        m_buffer = std::move(message);
    }

    int Connection::GetConnectionDescriptor() const {
        return m_socket_descriptor;
    }

    bool Connection::IsEqual(const Connection &connection) const {
        // I may wrong. but we can mix up connection between new socket with main socket
        //
        return m_is_connected == connection.IsConnected() && m_socket_descriptor == connection.GetConnectionDescriptor();
    }

    bool Connection::IsEqual(std::shared_ptr<Connection> connection) const {
        if(connection)
        {
            return IsEqual(*connection.get());
        }
        return false;
    }

    bool Connection::operator==(const Connection &other) const {
        return IsEqual(other);
    }

    bool Connection::operator==(std::shared_ptr<Connection> other) const {
        return IsEqual(other);
    }
}
