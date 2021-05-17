find_package(Qt5 COMPONENTS Core HttpServer Network REQUIRED)

set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

add_library(http_server STATIC
  http_server.cpp
  scripts_api.cpp
  runner_api.cpp
  scripts_cache.cpp
)

target_link_libraries(http_server Qt::Core Qt::HttpServer Qt::Network)
