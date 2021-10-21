#include "BerkeleyClient.h"

#include <cstring>
#include <string>

#include "TCPSocket.h"
#include "TCPConnection.h"
#include "PortHelper.h"

int main(int argc, char *argv[]) {
    if (argc < 4) {
        std::cout << "Please enter address and port and message" << std::endl;
    }

    Network::TCPSocket socket(std::string(argv[2],strlen(argv[2])), std::string(argv[1],strlen(argv[1])));
    socket.CreateSocket();
    Network::TCPConnection connection;
    connection.Connect(socket);
    connection.SetBuffer(std::string(argv[3], strlen(argv[3])));
    connection.Write();
    connection.Read();
    const auto message = connection.GetBuffer();
    std::cout << message << std::endl;
    return EXIT_SUCCESS;
}
