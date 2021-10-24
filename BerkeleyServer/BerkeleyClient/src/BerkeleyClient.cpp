#include "BerkeleyClient.h"

#include <cstring>
#include <string>
#include <algorithm>
#include <unistd.h>

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
    // user can enter message without \" symbol
    std::string message;
    for (int i = 4; i < argc; i++) {
        message += GetString(argv[i]) + " ";
    }

    auto connection = Network::NetworkHelper::MakeConnection(type_arg);
    connection->Connect(socket);
    if (connection->IsConnected()) {
        connection->SetBuffer(message);
        connection->Write();
        connection->Read();
        std::cout << "Receive message from server : " << connection->GetBuffer()<< std::endl;
    } else
        std::cerr << "Connect failed." << std::endl;
    return EXIT_SUCCESS;
}
