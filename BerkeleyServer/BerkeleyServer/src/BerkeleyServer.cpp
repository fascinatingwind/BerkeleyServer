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
        if (m_listening_port.empty()) {
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

    void BerkeleyServer::AcceptNewConnections(const std::vector<SockBasePtr> &incoming) {
        for (const auto &sockfd: incoming) {
            // new connections from listeners
            for (const auto &socket: m_listeners) {
                if (sockfd == socket) {
                    auto conn = NetworkHelper::MakeConnection(socket);
                    conn->Accept(socket);
                    m_event_manager.AppendSockFD(conn);
                    m_connection_map.emplace(conn->GetSock(), conn);
                }
            }
        }
    }

    void BerkeleyServer::SetPort(const std::string &port) {
        m_listening_port = port;
    }

    void BerkeleyServer::Run() {
        if (m_listening_port.empty()) {
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
                const auto fit = m_connection_map.find(sockfd->GetSock());
                if (fit != m_connection_map.end()) {
                    const auto&[connfd, conn] = *fit;
                    // connections for send/receive
                    std::async(&BerkeleyServer::SentResponse, this, conn);
                }
            }
        }
    }

    void BerkeleyServer::SentResponse(ConnectionPtr conn) {
        if (conn) {
            conn->Read();
            // bottleneck
            //Print(conn);
            ClientRequestParser parser;
            conn->SetBuffer(parser.GetResponse(conn->GetBuffer()));
            conn->Write();
            RemoveConnection(conn);
        }
    }

    void BerkeleyServer::RemoveConnection(ConnectionPtr conn) {
        if (conn) {
            std::lock_guard<std::mutex> lock(m_mutex);
            const int sockfd = conn->GetSock();
            // make sure what we dont delete udp socket
            const auto fit = std::find_if(m_listeners.begin(), m_listeners.end(),
                                          [sockfd](SocketPtr sock) { return sock->GetSock() == sockfd; });
            if (fit == m_listeners.end()) {
                m_connection_map.erase(sockfd);
                m_event_manager.RemoveConnection(conn);
            }
        }
    }

    void BerkeleyServer::Print(ConnectionPtr conn) {
        if (conn) {
            std::lock_guard<std::mutex> lock(m_mutex);
            std::cout << "Client sent message :" << conn->GetBuffer() << std::endl;
        }
    }
}