#include "StringConverter.h"

#include <sstream>

#include "StringSplitter.h"

namespace Server {
    std::vector<int> StringConverter::GetAllInt(const std::string &str) {
        // should be better way using streams
        const auto string_list = StringSplitter::Split(str);
        std::vector<int> result;
        for(const auto& string_item : string_list){
            int i;
            std::stringstream sstream(string_item);
            while ((sstream >> i)) {
                result.push_back(i);
            }
        }

        return result;
    }

    std::string StringConverter::GetString(const std::vector<int> &digits) {
        std::string result;
        for(const int value : digits)
        {
            result += std::to_string(value) + " ";
        }
        return result;
    }
}