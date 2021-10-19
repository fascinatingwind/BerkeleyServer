#ifndef BERKELEYSERVER_TCPSOCKET_H
#define BERKELEYSERVER_TCPSOCKET_H

#include <string>

#include "Socket.h"

namespace Network {
    class TCPSocket final : public Socket {
    public:
        explicit TCPSocket(size_t port, const std::string& address = "", bool is_listen = true);
    private:
        bool m_listen = true;
    };

    using TCPSocketPtr = std::shared_ptr<TCPSocket>;
}

#endif //BERKELEYSERVER_TCPSOCKET_H
