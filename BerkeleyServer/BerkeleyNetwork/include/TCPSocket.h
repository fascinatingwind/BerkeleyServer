#ifndef BERKELEYSERVER_TCPSOCKET_H
#define BERKELEYSERVER_TCPSOCKET_H

#include <string>

#include "Socket.h"

namespace Network {
    class TCPSocket final : public Socket {
    public:
        explicit TCPSocket(const std::string& port, const std::string& address = "");
        ~TCPSocket() override;

        void CreateSocket() override;

        void SetSockOpt() override;

        void Bind() override;

        void Listen() const override;

        [[nodiscard]] bool IsValid() const override;

        [[nodiscard]] int GetSocketDescriptor() const override;

        [[nodiscard]] addrinfo * GetAddrInfo() const override;

    protected:
        addrinfo *m_sockaddr = nullptr;
        int m_socket = -1;
    };

    using TCPSocketPtr = std::shared_ptr<TCPSocket>;
}

#endif //BERKELEYSERVER_TCPSOCKET_H
