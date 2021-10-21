#ifndef BERKELEYSERVER_UDPCONNECTION_H
#define BERKELEYSERVER_UDPCONNECTION_H

#include "Connection.h"
#include "UDPSocket.h"

struct sockaddr_storage;
struct sockaddr;

namespace Network {
    class UDPConnection final : public Connection{
    public:
        UDPConnection() = default;
        ~UDPConnection() override;

        void Read() override;

        void Write() override;

        void ReadAsync() override;

        void WriteAsync() override;

        void Accept(const Socket& socket) override;

        void Connect(const Socket& socket) override;

        std::string GetBuffer() override;

    private:
        int m_socket_descriptor = -1;
        struct sockaddr_storage m_remote_addr_storage = {};
        addrinfo *m_sockaddr = nullptr;
    };
}

#endif //BERKELEYSERVER_UDPCONNECTION_H
