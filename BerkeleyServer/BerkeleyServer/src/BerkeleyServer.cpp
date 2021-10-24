#include "BerkeleyServer.h"

#include <iostream>
#include <algorithm>
#include <vector>
#include <future>

#include "NetworkHelper.h"
#include "Socket.h"
#include "ClientRequestParser.h"

namespace Server {
    void BerkeleyServer::InitListenSockets() {
        if(m_listening_port.empty())
        {
            std::cerr << "Please setup port." << std::endl;
            return;
        }

        m_listeners.push_back(NetworkHelper::MakeSocket("tcp", "", m_listening_port));
        m_listeners.push_back(NetworkHelper::MakeSocket("udp", "", m_listening_port));

        for (const auto &socket: m_listeners) {
            socket->CreateSocket();
            socket->SetSockOpt();
            socket->Bind();
            socket->Listen();
            m_event_manager.AppendSockFD(socket);
        }

        // check listeners
        const auto it = std::find_if(m_listeners.begin(), m_listeners.end(),
                                     [](SocketPtr socket) { return !socket->IsValid(); });
        m_run = it == m_listeners.end();
    }

    void BerkeleyServer::AcceptNewConnections(const std::vector<SockBasePtr>& incoming) {
        for (const auto &sockfd: incoming) {
            // new connections from listeners
            for (const auto &socket: m_listeners) {
                if (sockfd == socket) {
                    auto conn = NetworkHelper::MakeConnection(socket);
                    conn->Accept(socket);
                    m_event_manager.AppendSockFD(conn);
                    m_connection_map.emplace(conn, conn);
                }
            }
        }
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

        InitListenSockets();

        while (m_run) {
            // return all sockets what have events
            const auto socks = m_event_manager.Poll();

            // new connections from listeners
            AcceptNewConnections(socks);

            for (const auto &sockfd: socks) {
                // io with clients
                const auto fit = m_connection_map.find(sockfd);
                if (fit != m_connection_map.end()) {
                    const auto&[connfd, conn] = *fit;
                    // connections for send/receive
                    auto future = std::async(&BerkeleyServer::SentResponse, this, conn);
                    future.wait();
                    RemoveConnection(conn);
                }
            }
        }
    }

    void BerkeleyServer::SentResponse(ConnectionPtr conn) {
        conn->Read();
        Print(conn);
        ClientRequestParser parser;
        conn->SetBuffer(parser.GetResponse(conn->GetBuffer()));
        conn->Write();
    }

    void BerkeleyServer::RemoveConnection(ConnectionPtr conn) {
        std::lock_guard<std::mutex> lock(m_mutex);
        m_connection_map.erase(conn);
        m_event_manager.RemoveConnection(conn);
    }

    void BerkeleyServer::Print(ConnectionPtr conn) {
        std::lock_guard<std::mutex> lock(m_mutex);
        std::cout << conn->GetBuffer() << std::endl;
    }
}