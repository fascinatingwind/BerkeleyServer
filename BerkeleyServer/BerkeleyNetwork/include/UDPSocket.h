#ifndef BERKELEYSERVER_UDPSOCKET_H
#define BERKELEYSERVER_UDPSOCKET_H

#include <string>

#include "Socket.h"

namespace Network {

    class UDPSocket : public Socket
    {
    public:
       explicit UDPSocket(const std::string& port, const std::string& address = "");

        void SetSockOpt() override {};

        void Listen() const override {};

    };

    using UDPSocketPtr = std::shared_ptr<UDPSocket>;
}

#endif //BERKELEYSERVER_UDPSOCKET_H
