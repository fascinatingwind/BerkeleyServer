#ifndef BERKELEYSERVER_TCPSOCKET_H
#define BERKELEYSERVER_TCPSOCKET_H

#include <Socket.h>

namespace Network {
    class TCPSocket final : public Socket {
    public:
        explicit TCPSocket(size_t port);
    };

    using TCPSocketPtr = std::shared_ptr<TCPSocket>;
}

#endif //BERKELEYSERVER_TCPSOCKET_H
