#ifndef BERKELEYSERVER_SOCKET_H
#define BERKELEYSERVER_SOCKET_H

#include <memory>
#include "PortHelper.h"

struct sockaddr_in;

namespace Network
{
    enum class CONNECTION_TYPE
    {
        TCP,
        UDP
    };

    class Socket
    {
    public:
        Socket() = delete;
        ~Socket();
        explicit Socket(CONNECTION_TYPE type = CONNECTION_TYPE::TCP, size_t port = PortHelper::TCP_PORT);

        [[nodiscard]] bool IsValid() const;
        [[nodiscard]] int GetSocketDescriptor() const;

    private:
        sockaddr_in* m_sockaddr;
        int m_socket;
        bool m_is_bind = false;
        sockaddr_in* InitSockAddr(size_t port);
    };
}
#endif //BERKELEYSERVER_SOCKET_H
