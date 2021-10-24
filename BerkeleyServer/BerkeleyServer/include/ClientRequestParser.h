#ifndef BERKELEYSERVER_CLIENTREQUESTPARSER_H
#define BERKELEYSERVER_CLIENTREQUESTPARSER_H

#include <string>

namespace Server {
    class ClientRequestParser {
    public:
        ClientRequestParser() = default;
        ~ClientRequestParser() = default;

        std::string GetResponse(const std::string& request) const;
    };
}

#endif //BERKELEYSERVER_CLIENTREQUESTPARSER_H
