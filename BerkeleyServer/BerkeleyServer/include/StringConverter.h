#ifndef BERKELEYSERVER_STRINGCONVERTER_H
#define BERKELEYSERVER_STRINGCONVERTER_H

#include <string>

namespace Server {
    class StringConverter {
    public:
        StringConverter() = delete;
        ~StringConverter() = delete;

        static int GetInt(const std::string& str);
    };
}

#endif //BERKELEYSERVER_STRINGCONVERTER_H
