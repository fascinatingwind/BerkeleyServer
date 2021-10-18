#include "UDPSocket.h"

#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

namespace Network
{
    UDPSocket::UDPSocket(size_t port)
    {
        m_socket = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP);
        m_sockaddr = InitSockAddr(port);
        if (bind(m_socket, (struct sockaddr *) m_sockaddr, sizeof *m_sockaddr)) {
            m_is_bind = true;
        }
    }
}