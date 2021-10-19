#include "UDPSocket.h"

#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>

namespace Network {
    UDPSocket::UDPSocket(size_t port, const std::string &address) {
        m_socket = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP);
        m_sockaddr = InitSockAddr(port);
        if (address.empty()) {
            m_sockaddr->sin_addr.s_addr = htonl(INADDR_ANY);
        } else {
            m_sockaddr->sin_addr.s_addr = inet_addr(address.c_str());
        }
        if (bind(m_socket, (struct sockaddr *) m_sockaddr, sizeof *m_sockaddr)) {
            m_is_bind = true;
        }
    }
}