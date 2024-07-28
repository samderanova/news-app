#include "crow.h"

#include "rss.hpp"

const std::vector<std::string> RSS_FEEDS;

// crow::logger log{crow::LogLevel::DEBUG};

int main()
{
    crow::SimpleApp app;

    CROW_ROUTE(app, "/")
    (
        []()
        {
            std::vector<json> output;
            for (const std::string &url : RSS_FEEDS)
            {

                try
                {
                    std::vector<json> j = rss::fetch_items(url);
                    for (json article : j)
                    {
                        output.push_back(article);
                    }
                }
                catch (const std::exception &e)
                {
                    // log << "ERROR: Failed to pull articles from " + url;
                    return crow::response(crow::status::INTERNAL_SERVER_ERROR);
                }
            }
            json out{{"items", output}};
            return crow::response(crow::status::OK, "application/json", out.dump());
        });

    app.port(18080)
        .multithreaded()
        .run();

    return 0;
}