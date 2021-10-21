#ifndef BERKELEYSERVER_TCPCONNECTION_H
#define BERKELEYSERVER_TCPCONNECTION_H

#include "Connection.h"
#include "TCPSocket.h"

struct sockaddr_storage;

namespace Network {
    class TCPConnection final : public Connection {
    public:
        TCPConnection() = default;

        ~TCPConnection() override;

        void Read() override;

        void Write() override;

        void ReadAsync() override;

        void WriteAsync() override;

        void Accept(const Socket& socket) override;

        void Connect(const Socket& socket) override;

        std::string GetBuffer() override;

    private:
        int m_socket_descriptor;
        struct sockaddr_storage m_remote_addr_storage;

        void SendBufferSize();
        uint32_t ReceiveBufferSize();
    };
}
#endif //BERKELEYSERVER_TCPCONNECTION_H
