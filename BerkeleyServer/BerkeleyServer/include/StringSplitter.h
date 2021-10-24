#ifndef BERKELEYSERVER_STRINGSPLITTER_H
#define BERKELEYSERVER_STRINGSPLITTER_H

#include <vector>
#include <string>

namespace Server {
    class StringSplitter {
    public:
        StringSplitter() = delete;
        ~StringSplitter() = delete;

        static std::vector<std::string> Split(const std::string& str, const std::string& delim = " ");
    };
}

#endif //BERKELEYSERVER_STRINGSPLITTER_H
