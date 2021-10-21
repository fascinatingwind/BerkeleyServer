#include "BerkeleyServer.h"

#include <cstdlib>
#include <sys/wait.h>
#include <iostream>

#include "TCPSocket.h"
#include "PortHelper.h"
#include "TCPConnection.h"

using namespace Network;

void sigchild_handler(int s) {
    while (waitpid(-1, nullptr, WNOHANG) > 0);
}

int main() {
    signal(SIGINT, [](int) { run = false; });

    //UDPSocket udp_socket(PortHelper::UDP_PORT);

    struct sigaction sa = {};
    sa.sa_handler = sigchild_handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_RESTART;
    if (sigaction(SIGCHLD, &sa, nullptr) == -1) {
        std::cerr << "Sigaction error." << std::endl;
        run = false;
    }
    TCPSocket socket(std::to_string(PortHelper::TCP_PORT));
    socket.CreateSocket();
    socket.SetSockOpt();
    socket.Bind();
    socket.Listen();

    while (run) {
        run = socket.IsValid();//&& udp_socket.IsValid();
        TCPConnection connection;
        connection.Accept(socket);
        connection.Read();
        std::cout << connection.GetBuffer() << std::endl;
        connection.SetBuffer("Hello world!");
        connection.Write();
        std::cout << connection.GetBuffer() << std::endl;
    }

    return EXIT_SUCCESS;
}
