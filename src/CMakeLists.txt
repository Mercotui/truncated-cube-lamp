find_package(Qt6 COMPONENTS Core HttpServer Network REQUIRED)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

add_executable(truncated_cube_lamp
    main.cpp
    http_server.cpp
    runner.cpp
)

target_link_libraries(truncated_cube_lamp Qt::Core Qt::HttpServer Qt::Network)
