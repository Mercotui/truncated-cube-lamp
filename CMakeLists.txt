cmake_minimum_required(VERSION 3.1.0)

project(truncated_cube_lamp VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
option(BUILD_UNIT_TESTS "Build unit tests" ON)
option(BUILD_SCREEN_TEST "Build screen controller test program" OFF)

enable_testing()
include(FetchContent)

if(BUILD_UNIT_TESTS)
  FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG main
  )
  FetchContent_GetProperties(googletest)

  if(NOT googletest_POPULATED)
    message("Downloading googletest")
    FetchContent_Populate(googletest)
    add_subdirectory(${googletest_SOURCE_DIR} ${googletest_BINARY_DIR})
    include_directories(
      ${googletest_SOURCE_DIR}/include
      ${googletest_SOURCE_DIR}
    )
  endif()
endif(BUILD_UNIT_TESTS)

FetchContent_Declare(
  rpi_ws281x
  GIT_REPOSITORY https://github.com/jgarff/rpi_ws281x.git
)
FetchContent_GetProperties(rpi_ws281x)

if(NOT rpi_ws281x_POPULATED)
  message("Downloading rpi_ws281x")
  FetchContent_Populate(rpi_ws281x)
  # this library uses a target name that is reserved by ctest,
  # so we need to disable the library's test
  set(CMAKE_POLICY_DEFAULT_CMP0077 NEW)
  set(BUILD_TEST OFF)
  add_subdirectory(${rpi_ws281x_SOURCE_DIR} ${rpi_ws281x_BINARY_DIR})
  include_directories(${rpi_ws281x_SOURCE_DIR}/include ${rpi_ws281x_SOURCE_DIR})
endif()

add_subdirectory(service)
add_subdirectory(libraries)
add_subdirectory(animations)
