#include "EventManager.h"

#include <algorithm>
#include <iostream>

namespace Network {
    void EventManager::AppendSockFD(SockBasePtr sock_base) {
        // add listener and connected
        if (sock_base) {
            const int con_desc = sock_base->GetSock();
            m_connection_list.emplace(con_desc, sock_base);

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

    std::vector<SockBasePtr> EventManager::Poll() {
        int ret = poll(m_fds.data(), m_fds.size(), 10000);
        switch (ret) {
            case 0:
                return {};
            case -1:
                std::cerr << "Error Poll" << std::endl;
                return {};
            default:
                return GetActiveSockFD();
        }
    }

    std::vector<SockBasePtr> EventManager::GetActiveSockFD() {
        std::vector<SockBasePtr> result;
        for (auto &item: m_fds) {
            const auto it = m_connection_list.find(item.fd);
            // not neccessary
            if (it == m_connection_list.end())
                continue;

            const auto&[fd, conn] = *it;
            if (item.revents & POLLIN) {
                result.push_back(conn);
            }
            // Need read man for this
            /*if (item.revents & POLLOUT) {
                result.emplace(IO_TYPE::WRITE, conn);
            }*/

            // POLLERR POLLHUP POLLNVAL missing
            // reset incoming event
            item.revents = 0;
        }

        return result;
    }
}