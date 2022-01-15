find_package(Qt5 COMPONENTS Core REQUIRED)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

add_executable(truncated_cube_lamp
    main.cpp
)

target_link_libraries(truncated_cube_lamp
    animation_runner
    http_server
    default_animations
    Qt::Core
)

add_subdirectory(animation_runner)
add_subdirectory(http_server)
add_subdirectory(screen)
add_subdirectory(scripts_cache)

install(TARGETS truncated_cube_lamp RUNTIME DESTINATION "/usr/local/bin")
install(FILES "truncated_cube_lamp.service" DESTINATION "/etc/systemd/system")
install(DIRECTORY DESTINATION "/var/lib/truncated_cube_lamp")