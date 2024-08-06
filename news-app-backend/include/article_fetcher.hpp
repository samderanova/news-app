#ifndef RSS_HPP
#define RSS_HPP

#include <string>
#include <vector>

#include "libpq-fe.h"
#include <nlohmann/json.hpp>

using json = nlohmann::json;

class ArticleFetcher
{
  public:
    ArticleFetcher();
    ~ArticleFetcher();

  private:
    std::vector<json> getArticlesFromUrl(const std::string &url);

    pg_conn *conn;
};

#endif
