find_package(Qt6 COMPONENTS Core Gui REQUIRED)

set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

add_library(screen STATIC
  screen_controller.cpp
  dummy_screen_controller.cpp
)

target_include_directories(screen INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(screen ws2811 Qt::Core Qt::Gui)

IF(BUILD_SCREEN_TEST)
  add_subdirectory(test)
ENDIF()
