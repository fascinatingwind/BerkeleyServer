#ifndef BERKELEYSERVER_SOCKET_H
#define BERKELEYSERVER_SOCKET_H

#include <memory>
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

    protected:
        sockaddr_in *m_sockaddr = nullptr;
        int m_socket = -1;
        bool m_is_bind = false;

        sockaddr_in *InitSockAddr(size_t port);
    };

    using SocketPtr = std::shared_ptr<Socket>;
}
#endif //BERKELEYSERVER_SOCKET_H
