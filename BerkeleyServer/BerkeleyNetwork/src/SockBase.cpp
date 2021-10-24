#include "SockBase.h"

namespace Network {
    int SockBase::GetSock() const {
        return m_sock_fd;
    }

    bool SockBase::operator==(const SockBase &other) const {
        return m_sock_fd == other.m_sock_fd;
    }

    bool SockBase::operator==(std::shared_ptr<SockBase> other) const {
        return m_sock_fd == other->m_sock_fd;
    }
}