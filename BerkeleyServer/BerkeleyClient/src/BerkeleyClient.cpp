#include "BerkeleyClient.h"

#include <cstring>
#include <string>
#include <algorithm>

#include "NetworkHelper.h"

std::string GetString(char *argv) {
    return {argv, strlen(argv)};
}

int main(int argc, char *argv[]) {
    if (argc < 5) {
        std::cout << "Please enter address, port, protocol and message" << std::endl;
        return EXIT_SUCCESS;
    }
// may crash if no ascii symbol entered;
    auto type_arg = GetString(argv[3]);
    std::transform(type_arg.begin(), type_arg.end(), type_arg.begin(),
                   [](unsigned char c) { return std::tolower(c); });
    const auto socket = Network::NetworkHelper::MakeSocket(type_arg, GetString(argv[1]),
                                                           GetString(argv[2]));
    socket->CreateSocket();

    auto connection = Network::NetworkHelper::MakeConnection(type_arg);
    connection->Connect(socket);
    if (connection->IsConnected()) {
        connection->SetBuffer(GetString(argv[4]));
        connection->Write();
        connection->Read();
        const auto message = connection->GetBuffer();
        std::cout << message << std::endl;
    } else
        std::cerr << "Connect failed." << std::endl;
    return EXIT_SUCCESS;
}
