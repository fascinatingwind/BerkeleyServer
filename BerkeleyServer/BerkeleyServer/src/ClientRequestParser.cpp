#include "ClientRequestParser.h"

#include <algorithm>
#include <numeric>

#include "StringConverter.h"

namespace Server {
    std::string ClientRequestParser::GetResponse(const std::string &request) const {
        std::vector<int> digits = StringConverter::GetAllInt(request);
        std::sort(digits.begin(), digits.end(), std::less());
        const auto sum = std::accumulate(digits.begin(), digits.end(), 0);
        return StringConverter::GetString(digits) + "\n" + std::to_string(sum);
    }
}