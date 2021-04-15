find_package(Qt6 COMPONENTS Core Gui Qml REQUIRED)

set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

add_library(animation_runner STATIC
  animation_runner.cpp
  screen_controller.cpp
  screen_interface_js.cpp
)

target_link_libraries(animation_runner ws2811 Qt::Core Qt::Gui Qt::Qml)

add_subdirectory(tests)
