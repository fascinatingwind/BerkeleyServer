#include "Socket.h"

#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

namespace Network {
    Socket::Socket(CONNECTION_TYPE type, size_t port) {
        m_socket = socket(PF_INET, SOCK_STREAM, type == CONNECTION_TYPE::TCP ? IPPROTO_TCP : IPPROTO_UDP);
        m_sockaddr = InitSockAddr(port);
        if(bind(m_socket, (struct sockaddr*) m_sockaddr, sizeof *m_sockaddr))
        {
            listen(m_socket, 10);
            m_is_bind = true;
        }
    }

    Socket::~Socket() {
        delete m_sockaddr;
        close(m_socket);
    }

    sockaddr_in* Socket::InitSockAddr(size_t port)  {
        auto sa = new sockaddr_in;
        sa->sin_family = AF_INET;
        sa->sin_port = htons(static_cast<uint16_t>(port));
        sa->sin_addr.s_addr = htonl(INADDR_ANY);
        return sa;
    }

    bool Socket::IsValid() const {
        return m_socket != -1 && m_is_bind;
    }

    int Socket::GetSocketDescriptor() const {
        return m_socket;
    }
}