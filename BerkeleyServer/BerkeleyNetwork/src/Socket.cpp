#include "Socket.h"

#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

namespace Network {
    Socket::~Socket() {
        delete m_sockaddr;
        close(m_socket);
    }

    sockaddr_in *Socket::InitSockAddr(size_t port) {
        auto sa = new sockaddr_in;
        sa->sin_family = AF_INET;
        sa->sin_port = htons(static_cast<uint16_t>(port));
        return sa;
    }

    bool Socket::IsValid() const {
        return m_socket != -1 && m_is_bind;
    }

    int Socket::GetSocketDescriptor() const {
        return m_socket;
    }
}