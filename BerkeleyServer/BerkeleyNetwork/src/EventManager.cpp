#include "EventManager.h"

#include <algorithm>
#include <iostream>

namespace Network {
    void EventManager::AppendConnection(SockBasePtr connection) {
        // add listener and connected
        if (connection) {
            const int con_desc = connection->GetSock();
            m_connection_list.insert({con_desc, connection});

            pollfd new_fd = {0};
            new_fd.fd = con_desc;
            new_fd.events = POLLIN;
            m_fds.push_back(new_fd);
        }
    }

    void EventManager::RemoveConnection(SockBasePtr connection) {
        if (connection) {
            m_connection_list.erase(connection->GetSock());

            const auto fit = std::find_if(m_fds.begin(), m_fds.end(),
                                       [&connection](const pollfd &fds) {
                                           return fds.fd == connection->GetSock();
                                       });
            if (fit != m_fds.end())
                m_fds.erase(fit);
        }
    }

    std::map<CONNECTION_TYPE, SockBasePtr> EventManager::Poll() {
        int ret = poll(m_fds.data(), m_fds.size(), 10000);
        switch (ret) {
            case 0:
                std::cerr << "Error Poll" << std::endl;
                return {};
            case -1:
                return {};
            default:
                return GetActiveConnections();
        }
    }

    std::map<CONNECTION_TYPE, SockBasePtr> EventManager::GetActiveConnections() {
        std::map<CONNECTION_TYPE, SockBasePtr> result;
        for (const auto &item: m_fds) {
            const auto it = m_connection_list.find(item.fd);
            // not neccessary
            if (it == m_connection_list.end())
                continue;

            const auto&[fd, conn] = *it;
            if (item.events & POLLIN) {
                result.emplace(CONNECTION_TYPE::READ, conn);
            }
            if (item.events & POLLOUT) {
                result.emplace(CONNECTION_TYPE::WRITE, conn);
            }
        }

        return result;
    }
}