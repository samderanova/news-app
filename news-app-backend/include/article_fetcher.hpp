#ifndef RSS_HPP
#define RSS_HPP

#include <string>
#include <vector>

#include "crow.h"
#include <nlohmann/json.hpp>

using json = nlohmann::json;

namespace rss
{
    std::vector<json> fetch_items(const std::string &url);
}

#endif