#include "TCPSocket.h"

#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

namespace Network
{
    TCPSocket::TCPSocket(size_t port)
    {
        m_socket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
        m_sockaddr = InitSockAddr(port);
        if (bind(m_socket, (struct sockaddr *) m_sockaddr, sizeof *m_sockaddr))
        {
            listen(m_socket, 10);
            m_is_bind = true;
        }
    }
}