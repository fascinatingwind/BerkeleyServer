#ifndef BERKELEYSERVER_EVENTMANAGER_H
#define BERKELEYSERVER_EVENTMANAGER_H

#include <map>
#include <vector>
// TODO try forward declaration to move it in cpp
#include <sys/poll.h>

#include "SockBase.h"

namespace Network {
    enum class CONNECTION_TYPE
    {
        READ,
        WRITE
    };

    class EventManager {
    public:
        EventManager() = default;

        ~EventManager() = default;

        void AppendConnection(SockBasePtr sock_base);

        std::map<CONNECTION_TYPE, SockBasePtr> Poll();

    protected:
        std::vector<pollfd> m_fds;
        std::map<int, SockBasePtr> m_connection_list;

        void RemoveConnection(SockBasePtr connection);
        std::map<CONNECTION_TYPE, SockBasePtr> GetActiveConnections();
    };
}
#endif //BERKELEYSERVER_EVENTMANAGER_H
