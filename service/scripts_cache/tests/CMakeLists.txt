find_package(Qt5 COMPONENTS Core Gui Qml Test REQUIRED)

set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

add_executable(scripts_cache_test scripts_cache_test.cpp)
add_test(scripts_cache_test scripts_cache_test)
target_link_libraries(scripts_cache_test scripts_cache
                      Qt::Core Qt::Gui Qt::Qml Qt::Test
                      gtest gmock)

add_executable(script_test script_test.cpp)
add_test(script_test script_test)
target_link_libraries(script_test scripts_cache
                      Qt::Core Qt::Gui Qt::Qml Qt::Test
                      gtest gmock)
