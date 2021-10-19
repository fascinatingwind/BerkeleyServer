#ifndef BERKELEYSERVER_SOCKET_H
#define BERKELEYSERVER_SOCKET_H

#include <memory>
#include <netdb.h>
#include "PortHelper.h"

struct sockaddr_in;

namespace Network {
    enum class CONNECTION_TYPE {
        TCP,
        UDP
    };

    class Socket {
    public:
        Socket() = default;

        virtual ~Socket();

        [[nodiscard]] bool IsValid() const;

        [[nodiscard]] int GetSocketDescriptor() const;

        [[nodiscard]] addrinfo *GetAddrInfo() const;

        void SetSockOpt();

        void Bind();

        void Listen() const;

    protected:
        addrinfo *m_sockaddr = nullptr;
        int m_socket = -1;

        addrinfo *InitAddrInfo();
    };

    using SocketPtr = std::shared_ptr<Socket>;
}
#endif //BERKELEYSERVER_SOCKET_H
