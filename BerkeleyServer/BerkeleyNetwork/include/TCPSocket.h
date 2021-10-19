#ifndef BERKELEYSERVER_TCPSOCKET_H
#define BERKELEYSERVER_TCPSOCKET_H

#include <string>

#include "Socket.h"

namespace Network {
    class TCPSocket final : public Socket {
    public:
        explicit TCPSocket(const std::string& port, const std::string& address = "");
    };

    using TCPSocketPtr = std::shared_ptr<TCPSocket>;
}

#endif //BERKELEYSERVER_TCPSOCKET_H
