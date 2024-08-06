#include "rss.hpp"

#include "feedpp/feedpp.h"

std::vector<json> rss::fetch_items(const std::string &url)
{
    feedpp::parser p = feedpp::parser();
    feedpp::feed f = p.parse_url(url);

    std::vector<json> items;

    for (feedpp::item &item : f.items)
    {
        json itemJson{{"title", item.title}, {"link", item.link}};
        items.push_back(itemJson);
    }

    return items;
}
