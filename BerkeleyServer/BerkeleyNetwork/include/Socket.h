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

        virtual ~Socket() = default;

        virtual bool IsValid() const = 0;

        virtual int GetSocketDescriptor() const = 0;

        virtual addrinfo *GetAddrInfo() const = 0;

        virtual void SetSockOpt() = 0;

        virtual void Bind() = 0;

        virtual void Listen() const = 0;

        virtual void CreateSocket() = 0;
    };

    using SocketPtr = std::shared_ptr<Socket>;
}
#endif //BERKELEYSERVER_SOCKET_H
