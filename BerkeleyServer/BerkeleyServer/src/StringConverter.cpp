#include "StringConverter.h"

#include <sstream>

namespace Server
{
    int StringConverter::GetInt(const std::string &str) {
        std::istringstream istream;
        int i;
        istream >> i;
        return i;
    }
}