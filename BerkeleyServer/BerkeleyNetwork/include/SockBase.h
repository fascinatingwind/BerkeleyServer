#ifndef BERKELEYSERVER_SOCKBASE_H
#define BERKELEYSERVER_SOCKBASE_H

#include <memory>

namespace Network {
    class SockBase {
    public:
        SockBase() = default;
        ~SockBase() = default;

        int GetSock() const;

    protected:
        int m_sock_fd = -1;
    };

    using SockBasePtr = std::shared_ptr<SockBase>;
}

#endif //BERKELEYSERVER_SOCKBASE_H
