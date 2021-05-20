find_package(Qt5 COMPONENTS Core REQUIRED)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

add_executable(truncated_cube_lamp
    main.cpp
)

target_link_libraries(truncated_cube_lamp animation_runner http_server
                      website Qt::Core)

add_subdirectory(animation_runner)
add_subdirectory(http_server)
add_subdirectory(screen)
