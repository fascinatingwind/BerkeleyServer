#include "BerkeleyServer.h"

#include <iostream>
#include <algorithm>
#include <vector>

#include "NetworkHelper.h"
#include "Socket.h"

namespace Server {
    std::vector<SocketPtr> BerkeleyServer::InitListenSockets() {
        std::vector<SocketPtr> listeners;
        if(m_listening_port.empty())
        {
            std::cerr << "Please setup port." << std::endl;
            return listeners;
        }

        listeners.push_back(NetworkHelper::MakeSocket("tcp", "", m_listening_port));
        listeners.push_back(NetworkHelper::MakeSocket("udp", "", m_listening_port));

        for (const auto &socket: listeners) {
            socket->CreateSocket();
            socket->SetSockOpt();
            socket->Bind();
            socket->Listen();
        }
        return listeners;
    }

    void BerkeleyServer::SetPort(const std::string &port) {
        m_listening_port = port;
    }

    void BerkeleyServer::Run() {
        if(m_listening_port.empty())
        {
            std::cerr << "Please setup port." << std::endl;
            return;
        }
        const auto listeners = InitListenSockets();

        for (const auto &sock: listeners)
            m_event_manager.AppendSockFD(sock);

        while (m_run) {
            // check listeners
            const auto it = std::find_if(listeners.begin(), listeners.end(),
                                         [](SocketPtr socket) { return !socket->IsValid(); });
            m_run = it == listeners.end();

            // return all sockets what have events
            const auto socks = m_event_manager.Poll();
            for (const auto &sockfd: socks) {
                // new connections from listeners
                for (const auto &socket: listeners) {
                    if (sockfd == socket) {
                        auto conn = NetworkHelper::MakeConnection(socket);
                        conn->Accept(socket);
                        m_event_manager.AppendSockFD(conn);
                        m_connection_map.emplace(conn, conn);
                    }
                }

                // io with clients
                const auto fit = m_connection_map.find(sockfd);
                if (fit != m_connection_map.end()) {
                    const auto&[connfd, conn] = *fit;
                    // connections for send/receive
                    // TODO Async
                    conn->Read();
                    std::cout << conn->GetBuffer() << std::endl;
                    conn->SetBuffer("Hello World");
                    conn->Write();
                    m_connection_map.erase(conn);
                    m_event_manager.RemoveConnection(conn);
                }
            }
        }
    }
}