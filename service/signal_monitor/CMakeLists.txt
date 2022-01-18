find_package(Qt5 COMPONENTS Core REQUIRED)

set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

add_library(signal_monitor STATIC
  signal_monitor.cpp
)

target_link_libraries(signal_monitor Qt::Core)

target_include_directories(signal_monitor INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
