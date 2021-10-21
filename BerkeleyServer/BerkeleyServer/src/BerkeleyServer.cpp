#include "BerkeleyServer.h"

#include <cstdlib>
#include <sys/wait.h>
#include <iostream>
#include <cstring>

#include "NetworkHelper.h"

using namespace Network;

std::string GetString(char *argv) {
    return {argv, strlen(argv)};
}

void sigchild_handler(int s) {
    while (waitpid(-1, nullptr, WNOHANG) > 0);
}

int main(int argc, char* argv[]) {
    if(argc < 2)
    {
        std::cerr << "Please enter port for listening" << std::endl;
        return EXIT_SUCCESS;
    }

    signal(SIGINT, [](int) { run = false; });

    struct sigaction sa = {};
    sa.sa_handler = sigchild_handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_RESTART;
    if (sigaction(SIGCHLD, &sa, nullptr) == -1) {
        std::cerr << "Sigaction error." << std::endl;
        run = false;
    }
    const auto port = GetString(argv[1]);
    auto tcp_socket = NetworkHelper::MakeSocket("tcp", "", port);
    auto udp_socket = NetworkHelper::MakeSocket("udp", "", port);

    for(const auto& socket : {tcp_socket, udp_socket}) {
        socket->CreateSocket();
        socket->SetSockOpt();
        socket->Bind();
        socket->Listen();
    }

    while (run) {
        run = tcp_socket->IsValid();
        auto connection = NetworkHelper::MakeConnection("tcp");
        connection->Accept(tcp_socket);
        if(connection->IsConnected()) {
            connection->Read();
            std::cout << connection->GetBuffer() << std::endl;
            connection->SetBuffer("Hello world!");
            connection->Write();
            std::cout << connection->GetBuffer() << std::endl;
        }
        else
        {
            std::cerr << "Connection problem." << std::endl;
        }
    }

    return EXIT_SUCCESS;
}
