find_package(Qt5 COMPONENTS Core Gui REQUIRED)

set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

add_library(screen STATIC
  screen_controller.cpp
  dummy_screen_controller.cpp
)

target_link_libraries(screen ws2811 Qt::Core Qt::Gui)

IF(BUILD_SCREEN_DEMO)
  add_subdirectory(demo)
ENDIF()
