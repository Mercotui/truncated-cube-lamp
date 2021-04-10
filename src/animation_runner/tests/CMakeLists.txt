find_package(Qt6 COMPONENTS Core Gui Qml Test REQUIRED)

set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

add_executable(animation_runner_test animation_runner_test.cpp)

add_test(animation_runner_test animation_runner_test)

target_link_libraries(animation_runner_test animation_runner
                      Qt::Core Qt::Gui Qt::Qml Qt::Test
                      gtest gmock)
