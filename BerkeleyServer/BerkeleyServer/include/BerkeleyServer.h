#pragma once
#ifndef BERKELEY_SERVER_H
#define BERKELEY_SERVER_H

#include <mutex>

#include "EventManager.h"
#include "Socket.h"
#include "Connection.h"

namespace Server {
    using namespace Network;

    class BerkeleyServer {
    public:
        BerkeleyServer() = default;

        ~BerkeleyServer() = default;

        void SetPort(const std::string &port);

        void Run();

    protected:
        std::mutex m_mutex;
        std::string m_listening_port;
        EventManager m_event_manager;
        std::map<int, ConnectionPtr> m_connection_map;
        bool m_run = true;

    private:
        std::vector<SocketPtr> m_listeners;

        void InitListenSockets();

        void AcceptNewConnections(const std::vector<SockBasePtr> &incoming);

        void SentResponse(ConnectionPtr conn);

        void RemoveConnection(ConnectionPtr conn);

        void Print(ConnectionPtr conn);
    };
}

#endif // !BERKELEY_SERVER_H

