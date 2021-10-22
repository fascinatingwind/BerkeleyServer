#include "NetworkHelper.h"

#include <netdb.h>

#include "TCPSocket.h"
#include "UDPSocket.h"
#include "TCPConnection.h"
#include "UDPConnection.h"

namespace Network {
    bool IsTCP(const std::string &type) {
        const auto fit = type.find("tcp");
        return fit != std::string::npos;
    }

    ConnectionPtr NetworkHelper::MakeConnection(const std::string &type) {
        if (IsTCP(type))
            return std::make_shared<Network::TCPConnection>();
        else
            return std::make_shared<Network::UDPConnection>();
    }

    SocketPtr NetworkHelper::MakeSocket(const std::string &type, const std::string &address, const std::string &port) {
        if (IsTCP(type))
            return std::make_shared<Network::TCPSocket>(port, address);
        else
            return std::make_shared<Network::UDPSocket>(port, address);
    }

    ConnectionPtr NetworkHelper::MakeConnection(SocketPtr socket) {
        const auto sock_info = socket->GetAddrInfo();
        switch (sock_info->ai_socktype) {
            case SOCK_STREAM:
                return std::make_shared<TCPConnection>();
            case SOCK_DGRAM:
                return std::make_shared<UDPConnection>();
            default:
                return nullptr;
        }
    }
}