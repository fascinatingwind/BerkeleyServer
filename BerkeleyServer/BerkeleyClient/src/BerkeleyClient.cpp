#include "BerkeleyClient.h"

#include <cstring>
#include <string>
#include <algorithm>

#include "Socket.h"
#include "Connection.h"
#include "UDPSocket.h"
#include "UDPConnection.h"
#include "TCPSocket.h"
#include "TCPConnection.h"

std::string GetString(char *argv) {
    return {argv, strlen(argv)};
}

bool IsTCP(const std::string &type) {
    const auto fit = type.find("tcp");
    return fit != std::string::npos;
}

Network::SocketPtr MakeSocket(const std::string &type, const std::string &address, const std::string &port) {
    if (IsTCP(type))
        return std::make_shared<Network::UDPSocket>(port, address);
    else
        return std::make_shared<Network::TCPSocket>(port, address);
}

Network::ConnectionPtr MakeConnection(const std::string &type) {
    if (IsTCP(type))
        return std::make_shared<Network::TCPConnection>();
    else
        return std::make_shared<Network::UDPConnection>();
}

int main(int argc, char *argv[]) {
    if (argc < 5) {
        std::cout << "Please enter address, port, protocol and message" << std::endl;
    }
// may crash if no ascii symbol entered;
    auto type_arg = GetString(argv[3]);
    std::transform(type_arg.begin(), type_arg.end(), type_arg.begin(),
                   [](unsigned char c) { return std::tolower(c); });
    const auto socket = MakeSocket(type_arg, GetString(argv[2]), GetString(argv[1]));
    socket->CreateSocket();

    auto connection = MakeConnection(type_arg);
    connection->Connect(socket);
    connection->SetBuffer(GetString(argv[4]));
    connection->Write();
    connection->Read();
    const auto message = connection->GetBuffer();
    std::cout << message << std::endl;
    return EXIT_SUCCESS;
}
