find_package(Qt6 COMPONENTS Core HttpServer Network Gui Qml REQUIRED)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

add_executable(truncated_cube_lamp
    main.cpp
    http_server.cpp
)

target_link_libraries(truncated_cube_lamp animation_runner website
                      Qt::Core Qt::HttpServer Qt::Network Qt::Gui Qt::Qml)

add_subdirectory(animation_runner)
