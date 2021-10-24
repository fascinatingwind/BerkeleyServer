#include <cstdlib>
#include <iostream>
#include <sys/wait.h>
#include <cstring>

#include "BerkeleyServer.h"

// should be inline
std::string GetString(char *argv) {
    return {argv, strlen(argv)};
}

void sigchild_handler(int s) {
    while (waitpid(-1, nullptr, WNOHANG) > 0);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        std::cerr << "Please enter port for listening" << std::endl;
        return EXIT_SUCCESS;
    }
    // sigaction for terminal signals
    signal(SIGINT, [](int) { exit(0); });

    struct sigaction sa = {};
    sa.sa_handler = sigchild_handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_RESTART;
    if (sigaction(SIGCHLD, &sa, nullptr) == -1) {
        std::cerr << "Sigaction error." << std::endl;
        exit(0);
    }

    Server::BerkeleyServer server;
    server.SetPort(GetString(argv[1]));
    server.Run();

    return EXIT_SUCCESS;
}