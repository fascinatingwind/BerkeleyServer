#include "NetworkHelper.h"

#include "TCPSocket.h"
#include "UDPSocket.h"
#include "TCPConnection.h"
#include "UDPConnection.h"

namespace Network
{
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

    SocketPtr NetworkHelper::MakeSocket(const std::string &type, const std::string& address, const std::string& port) {
        if (IsTCP(type))
            return std::make_shared<Network::UDPSocket>(port, address);
        else
            return std::make_shared<Network::TCPSocket>(port, address);
    }
}