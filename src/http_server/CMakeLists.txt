find_package(Qt6 COMPONENTS Core HttpServer Network REQUIRED)

set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

add_library(http_server STATIC
  http_server.cpp
  api/scripts_api.cpp
  api/runner_api.cpp
)

target_link_libraries(http_server scripts_cache
                      Qt::Core Qt::HttpServer Qt::Network)
