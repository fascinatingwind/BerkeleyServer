#ifndef BERKELEYSERVER_NETWORKHELPER_H
#define BERKELEYSERVER_NETWORKHELPER_H

#include <string>

#include "Socket.h"
#include "Connection.h"

namespace Network {
    class NetworkHelper {
    public:
        NetworkHelper() = delete;

        ~NetworkHelper() = delete;

        static SocketPtr MakeSocket(const std::string& type, const std::string& address, const std::string& port);
        static ConnectionPtr MakeConnection(const std::string& type);
    };
}

#endif //BERKELEYSERVER_NETWORKHELPER_H
