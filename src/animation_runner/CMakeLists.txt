find_package(Qt5 COMPONENTS Core Gui Qml REQUIRED)

set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

add_library(animation_runner STATIC
  animation_runner.cpp
  screen_interface_js.cpp
)

target_link_libraries(animation_runner js_libraries screen
                      Qt::Core Qt::Gui Qt::Qml)

if(BUILD_UNIT_TESTS)
  add_subdirectory(tests)
endif(BUILD_UNIT_TESTS)
