find_package(Qt6 COMPONENTS Core HttpServer Network Qml REQUIRED)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

add_executable(truncated_cube_lamp
    main.cpp
    http_server.cpp
    animation_runner.cpp
)

target_link_libraries(truncated_cube_lamp website Qt::Core Qt::HttpServer Qt::Network Qt::Qml)
