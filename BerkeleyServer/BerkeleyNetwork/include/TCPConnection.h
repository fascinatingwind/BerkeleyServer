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

        void Accept(SocketPtr socket) override;

        void Connect(SocketPtr socket) override;

        std::string GetBuffer() override;

    private:
        // we create own socket discription only connect
        bool is_need_close_socket = false;
        void SendBufferSize();
        uint32_t ReceiveBufferSize();
    };
}
#endif //BERKELEYSERVER_TCPCONNECTION_H
