#include "SockBase.h"
namespace Network
{
    int SockBase::GetSock() const {
        return m_sock_fd;
    }
}