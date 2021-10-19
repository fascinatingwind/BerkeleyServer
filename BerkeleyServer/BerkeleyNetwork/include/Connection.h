#ifndef BERKELEYSERVER_CONNECTION_H
#define BERKELEYSERVER_CONNECTION_H

#include <memory>
#include <string>

#include "Socket.h"

namespace Network {
    class Connection {
    public:
        Connection() = default;

        virtual ~Connection() = default;

        virtual void Read() = 0;

        virtual void Write() = 0;

        virtual void ReadAsync() = 0;

        virtual void WriteAsync() = 0;

        virtual void Accept(SocketPtr socket) = 0;
        virtual void Connect(SocketPtr socket) = 0;

        virtual std::string GetBuffer() = 0;

        virtual void SetBuffer(std::string message) { m_buffer = std::move(message); }

    protected:
        std::string m_buffer;
    };

    using ConnectionPtr = std::shared_ptr<Connection>;
}

#endif //BERKELEYSERVER_CONNECTION_H
