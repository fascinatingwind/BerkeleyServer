#ifndef BERKELEYSERVER_CONNECTION_H
#define BERKELEYSERVER_CONNECTION_H

#include <memory>
#include <string>
#include <vector>
//TODO remove include, use forward definition
#include <sys/socket.h>

#include "Socket.h"

namespace Network {
    class Connection {
    public:
        Connection() = default;

        virtual ~Connection() = default;

        virtual void Read() = 0;

        virtual void Write() = 0;

        virtual void Accept(SocketPtr socket) = 0;

        virtual void Connect(SocketPtr socket) = 0;

        virtual std::string GetBuffer() = 0;

        virtual void SetBuffer(std::string message);

        bool IsConnected() const;

        int GetConnectionDescriptor() const;

        bool operator==(const Connection &other) const;

        bool operator==(std::shared_ptr<Connection> other) const;

    protected:
        struct sockaddr_storage m_remote_addr_storage = {};
        std::string m_buffer;
        int m_socket_descriptor = -1;

        // true if we create are socket connection.
        // false if we got descriptor from socket and no need close it
        bool m_is_connected = false;

        bool IsEqual(std::shared_ptr<Connection> connection) const;

        bool IsEqual(const Connection &connection) const;
    };

    using ConnectionPtr = std::shared_ptr<Connection>;
}

#endif //BERKELEYSERVER_CONNECTION_H
