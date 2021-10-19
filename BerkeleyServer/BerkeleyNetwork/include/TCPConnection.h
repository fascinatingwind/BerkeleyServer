#ifndef BERKELEYSERVER_TCPCONNECTION_H
#define BERKELEYSERVER_TCPCONNECTION_H

#include "Connection.h"
#include "TCPSocket.h"

namespace Network {
    class TCPConnection final : public Connection {
    public:
        TCPConnection() = default;

        ~TCPConnection() override;

        void Read() override;

        void Write() override;

        void ReadAsync() override;

        void WriteAsync() override;

        void Accept(SocketPtr socket) override;

        void Connect(SocketPtr socket) override;

        std::string GetBuffer() override;

    private:
        int m_connection_descriptor;

        void LogIfError(const std::string& message) const;
    };
}
#endif //BERKELEYSERVER_TCPCONNECTION_H
