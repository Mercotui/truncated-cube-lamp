cmake_minimum_required(VERSION 3.1.0)

project(truncated_cube_lamp VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
option(BUILD_TESTS "Build unit tests" ON)
option(BUILD_SCREEN_DEMO "Build screen controller demo program" OFF)

if(BUILD_TESTS)
  enable_testing()
endif(BUILD_TESTS)

find_package(Qt5 COMPONENTS Core REQUIRED)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
include_directories(${CMAKE_SOURCE_DIR})

add_executable(truncated_cube_lamp
    main.cpp
)

target_link_libraries(truncated_cube_lamp
    animation_runner
    http_server
    default_animations
    signal_monitor
    Qt::Core
)

if(BUILD_TESTS)
  add_subdirectory(thirdparty/googletest)
endif(BUILD_TESTS)

# this library uses a target name that is reserved by ctest,
# so we need to disable the library's test
set(CMAKE_POLICY_DEFAULT_CMP0077 NEW)
set(BUILD_TEST OFF)
add_subdirectory(thirdparty/rpi_ws281x)

add_subdirectory(animation_runner)
add_subdirectory(http_server)
add_subdirectory(screen)
add_subdirectory(scripts_cache)
add_subdirectory(signal_monitor)

include(cmake/animations.cmake)
include(cmake/libraries.cmake)

install(TARGETS truncated_cube_lamp RUNTIME DESTINATION "/usr/local/bin")
install(FILES "truncated_cube_lamp.service" DESTINATION "/etc/systemd/system")
install(DIRECTORY DESTINATION "/var/lib/truncated_cube_lamp")
