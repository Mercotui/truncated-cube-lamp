find_package(Qt5 COMPONENTS Core REQUIRED)

set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

add_library(scripts_cache STATIC
  script.cpp
  scripts_cache.cpp
)

target_link_libraries(scripts_cache Qt::Core)

target_include_directories(scripts_cache INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

if(BUILD_UNIT_TESTS)
  add_subdirectory(tests)
endif(BUILD_UNIT_TESTS)
