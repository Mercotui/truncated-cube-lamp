find_package(Qt5 COMPONENTS Core Gui REQUIRED)

set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

add_executable(screen_controller_demo main.cpp user_interface.cpp)

target_link_libraries(screen_controller_demo screen curses Qt::Core Qt::Gui)
