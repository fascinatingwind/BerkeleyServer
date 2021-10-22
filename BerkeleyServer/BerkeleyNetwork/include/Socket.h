#ifndef BERKELEYSERVER_SOCKET_H
#define BERKELEYSERVER_SOCKET_H

#include <memory>

#include "SockBase.h"

struct addrinfo;

namespace Network {
    class Socket : public SockBase {
    public:
        Socket() = default;

        virtual ~Socket();

        virtual bool IsValid() const;

        virtual addrinfo *GetAddrInfo() const;

        virtual void SetSockOpt();

        virtual void Bind();

        virtual void Listen() const;

        virtual void CreateSocket();

    protected:
        addrinfo *m_sockaddr = nullptr;
    };

    using SocketPtr = std::shared_ptr<Socket>;
}
#endif //BERKELEYSERVER_SOCKET_H
