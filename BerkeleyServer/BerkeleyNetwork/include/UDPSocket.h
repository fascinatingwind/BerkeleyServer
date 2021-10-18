#ifndef BERKELEYSERVER_UDPSOCKET_H
#define BERKELEYSERVER_UDPSOCKET_H

#include "Socket.h"

namespace Network {

    class UDPSocket : public Socket
    {
    public:
       explicit UDPSocket(size_t port);
    };

    using UDPSocketPtr = std::shared_ptr<UDPSocket>;
}

#endif //BERKELEYSERVER_UDPSOCKET_H
