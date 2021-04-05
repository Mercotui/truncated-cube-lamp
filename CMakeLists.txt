cmake_minimum_required(VERSION 3.1.0)

project(truncated_cube_lamp VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)

FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
)
FetchContent_GetProperties(googletest)

if(NOT googletest_POPULATED)
  message("Downloading googletest")
  FetchContent_Populate(googletest)
  add_subdirectory(${googletest_SOURCE_DIR} ${googletest_BINARY_DIR})
  include_directories(${googletest_SOURCE_DIR}/include ${googletest_SOURCE_DIR})
endif()

add_subdirectory(src)
add_subdirectory(website)
