#ifndef BERKELEYSERVER_SOCKET_H
#define BERKELEYSERVER_SOCKET_H

#include <memory>
#include <netdb.h>
#include "PortHelper.h"

struct sockaddr_in;

namespace Network {
    class Socket {
    public:
        Socket() = default;

        virtual ~Socket();

        virtual bool IsValid() const;

        virtual int GetSocketDescriptor() const;

        virtual addrinfo *GetAddrInfo() const;

        virtual void SetSockOpt();

        virtual void Bind();

        virtual void Listen() const;

        virtual void CreateSocket();

    protected:
        addrinfo *m_sockaddr = nullptr;
        int m_socket = -1;
    };

    using SocketPtr = std::shared_ptr<Socket>;
}
#endif //BERKELEYSERVER_SOCKET_H
