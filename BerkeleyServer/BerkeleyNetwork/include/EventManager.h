#ifndef BERKELEYSERVER_EVENTMANAGER_H
#define BERKELEYSERVER_EVENTMANAGER_H

#include <map>
#include <vector>
// TODO try forward declaration to move it in cpp
#include <sys/poll.h>

#include "SockBase.h"

namespace Network {
    class EventManager {
    public:
        EventManager() = default;

        ~EventManager() = default;

        void AppendSockFD(SockBasePtr sock_base);

        std::vector<SockBasePtr> Poll();
        void RemoveConnection(SockBasePtr connection);

    protected:
        std::vector<pollfd> m_fds;
        std::map<int, SockBasePtr> m_connection_list;
        std::vector<SockBasePtr> GetActiveSockFD();
    };
}
#endif //BERKELEYSERVER_EVENTMANAGER_H
