#ifndef BERKELEYSERVER_EVENTMANAGER_H
#define BERKELEYSERVER_EVENTMANAGER_H

#include <map>
#include <vector>
// TODO try forward declaration to move it in cpp
#include <sys/poll.h>

#include "Connection.h"

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

        void AppendConnection(ConnectionPtr connection);

        std::map<CONNECTION_TYPE, ConnectionPtr> Poll();

    protected:
        std::vector<pollfd> m_fds;
        ConnectionPtr m_listener;
        std::map<int, ConnectionPtr> m_connection_list;

        void RemoveConnection(ConnectionPtr connection);
        std::map<CONNECTION_TYPE, ConnectionPtr> GetActiveConnections();
    };
}
#endif //BERKELEYSERVER_EVENTMANAGER_H
