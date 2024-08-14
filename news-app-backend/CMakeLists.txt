cmake_minimum_required(VERSION 3.20)
project(NewsAppBackend VERSION 1.0)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 17)

find_package(PostgreSQL REQUIRED spdlog REQUIRED)

add_executable(NewsAppBackend src/main.cpp src/article_fetcher.cpp
                              src/article_recommender.cpp src/helpers.cpp)

target_include_directories(
  NewsAppBackend PRIVATE src include /usr/include/libxml2
                         /usr/include/postgresql)

include(FetchContent)
FetchContent_Declare(cpr GIT_REPOSITORY https://github.com/libcpr/cpr.git)
FetchContent_Declare(json GIT_REPOSITORY https://github.com/nlohmann/json.git)
FetchContent_MakeAvailable(cpr json)

target_link_libraries(
  NewsAppBackend PRIVATE nlohmann_json::nlohmann_json cpr::cpr feedpp armadillo
                         PostgreSQL::PostgreSQL spdlog::spdlog)
