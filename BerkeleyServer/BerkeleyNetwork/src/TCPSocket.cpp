#include "TCPSocket.h"

#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>

namespace Network {
    TCPSocket::TCPSocket(size_t port, const std::string& address, bool is_listen)
            : m_listen(is_listen) {
        m_socket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
        m_sockaddr = InitSockAddr(port);
        if (address.empty()) {
            m_sockaddr->sin_addr.s_addr = htonl(INADDR_ANY);
        } else {
            inet_pton(AF_INET, address.c_str(), &m_sockaddr->sin_addr);
        }
        if (bind(m_socket, (struct sockaddr *) m_sockaddr, sizeof *m_sockaddr)) {
            if (m_listen)
                listen(m_socket, 10);
            m_is_bind = true;
        }
    }
}