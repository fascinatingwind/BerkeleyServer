#include "StringSplitter.h"

namespace Server {
    std::vector<std::string> StringSplitter::Split(const std::string &str, const std::string &delim) {
        std::vector<std::string> lines;
        std::size_t current, previous = 0;
        current = str.find_first_of(delim);
        while (current != std::string::npos) {
            lines.push_back(str.substr(previous, current - previous));
            previous = current + 1;
            current = str.find_first_of(delim, previous);
        }
        const auto last_line = str.substr(previous, current - previous);
        if(!last_line.empty())
            lines.push_back(last_line);
        return lines;
    }
}