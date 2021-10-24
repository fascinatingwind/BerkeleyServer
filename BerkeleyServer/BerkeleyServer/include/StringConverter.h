#ifndef BERKELEYSERVER_STRINGCONVERTER_H
#define BERKELEYSERVER_STRINGCONVERTER_H

#include <string>
#include <vector>

namespace Server {
    class StringConverter {
    public:
        StringConverter() = delete;
        ~StringConverter() = delete;

        // Can make template for other types
        static std::vector<int> GetAllInt(const std::string& str);

        static std::string GetString(const std::vector<int>& digits);
    };
}

#endif //BERKELEYSERVER_STRINGCONVERTER_H
