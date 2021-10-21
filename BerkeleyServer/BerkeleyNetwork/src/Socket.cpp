#include "Socket.h"

#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <iostream>
#include <cstring>

namespace Network {
  /*  Socket::~Socket() {
        freeaddrinfo(m_sockaddr);
        close(m_socket);
    }
*/
    /*addrinfo Socket::InitAddrInfo() {
        addrinfo sa = {};
        memset(&sa, 0, sizeof sa);
        sa.ai_family = AF_INET;
        sa.ai_flags = AI_PASSIVE;
        return sa;
    }

    bool Socket::IsValid() const {
        return m_socket > 0;
    }

    int Socket::GetSocketDescriptor() const {
        return m_socket;
    }

    addrinfo *Socket::GetAddrInfo() const {
        return m_sockaddr;
    }*/

  /*  void Socket::Bind() {
        if (IsValid() && m_sockaddr != nullptr) {
            int result = bind(m_socket, m_sockaddr->ai_addr, m_sockaddr->ai_addrlen);
            if (result < 0)
                std::cerr << "Socket bind error" << std::endl;
        }
    }

    void Socket::Listen() const {
        if (IsValid()) {
            listen(m_socket, 10);
        }
    }
*/
 /*   void Socket::SetSockOpt() {
        if (IsValid()) {
            int yes = 1;

            if (setsockopt(m_socket, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1) {
                std::cerr << "Set sockopt error" << std::endl;
            }
        }
    }*/
}
