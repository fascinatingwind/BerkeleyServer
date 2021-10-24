#pragma once
#ifndef BERKELEY_SERVER_H
#define BERKELEY_SERVER_H

#include "EventManager.h"
#include "Socket.h"
#include "Connection.h"

namespace Server {
    using namespace Network;

    class BerkeleyServer {
    public:
        BerkeleyServer() = default;

        ~BerkeleyServer() = default;

        void SetPort(const std::string& port);
        void Run();

    protected:
        bool m_run = true;
        std::string m_listening_port;
        EventManager m_event_manager;
        std::map<SockBasePtr, ConnectionPtr> m_connection_map;

    private:
        std::vector<SocketPtr> m_listeners;
        void InitListenSockets();
        void AcceptNewConnections(const std::vector<SockBasePtr>& incoming);
    };
}

#endif // !BERKELEY_SERVER_H

