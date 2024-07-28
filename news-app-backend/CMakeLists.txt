cmake_minimum_required(VERSION 3.20)
project(NewsAppBackend VERSION 1.0)
find_package(cpr REQUIRED)

add_executable(NewsAppBackend src/main.cpp src/rss.cpp)

target_include_directories(NewsAppBackend PRIVATE src include)
target_include_directories(NewsAppBackend PRIVATE /usr/include/libxml2)
target_link_libraries(NewsAppBackend PRIVATE cpr::cpr)
target_link_libraries(NewsAppBackend PRIVATE feedpp)

include(FetchContent)
FetchContent_Declare(cpr GIT_REPOSITORY https://github.com/libcpr/cpr.git)
FetchContent_Declare(json GIT_REPOSITORY https://github.com/nlohmann/json.git)
FetchContent_MakeAvailable(cpr json)

target_link_libraries(NewsAppBackend PRIVATE nlohmann_json::nlohmann_json)
