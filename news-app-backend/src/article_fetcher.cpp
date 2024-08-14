#include "article_fetcher.hpp"

#include "feedpp/feedpp.h"
#include "libpq-fe.h"
#include "spdlog/spdlog.h"

#include "helpers.hpp"

ArticleFetcher::ArticleFetcher()
{
    std::string host = getEnvVar("NEWS_APP_PQ_HOST");
    std::string port = getEnvVar("NEWS_APP_PQ_PORT");
    std::string user = getEnvVar("NEWS_APP_PQ_USER");
    std::string password = getEnvVar("NEWS_APP_PQ_PASSWORD");

    std::ostringstream connStream;
    connStream << "host=" << host << " " << "port=" << port << " " << "user=" << user << " " << "password=" << password;

    conn = PQconnectdb(connStream.str().c_str());

    spdlog::info("Successfully established connection to PostgreSQL database");
}

ArticleFetcher::~ArticleFetcher()
{
    PQfinish(conn);
    spdlog::info("Successfully closed connection to PostgreSQL database");
}

std::vector<json> ArticleFetcher::getArticlesFromUrl(const std::string &url)
{
    spdlog::info("Fetching articles from " + url);
    feedpp::parser p = feedpp::parser();
    feedpp::feed f = p.parse_url(url);
    spdlog::info("Successfully parsed articles from " + url);

    std::vector<json> items;
    for (feedpp::item &item : f.items)
    {
        json itemJson{{"title", item.title}, {"link", item.link}};
        items.push_back(itemJson);
    }
    return items;
}
