find_package(Qt5 COMPONENTS Core REQUIRED)

set(CMAKE_AUTORCC ON)

# Set animations file paths
set(ANIMATION_FILES_DIR ${CMAKE_SOURCE_DIR}/../animations)
set(ANIMATION_QRC ${CMAKE_CURRENT_BINARY_DIR}/animations.qrc)
set(ANIMATION_QRC_PREFIX "animations")
file(GLOB_RECURSE ANIMATION_FILES CONFIGURE_DEPENDS ${ANIMATION_FILES_DIR}/*.js)

# Comand to generate QRC
add_custom_command(
    OUTPUT
        ${ANIMATION_QRC}
    DEPENDS
        ${ANIMATION_FILES}
    COMMAND
      ${CMAKE_COMMAND}
      -Dqrc_file=${ANIMATION_QRC}
      -Dsource_files_dir=${ANIMATION_FILES_DIR}
      -Dqrc_prefix=${ANIMATION_QRC_PREFIX}
      "-Dsource_files=${ANIMATION_FILES}"
      -P ${CMAKE_SOURCE_DIR}/cmake/qrc_generator.cmake
    COMMENT
        "Generating animations.qrc"
    VERBATIM
)

# Use generated QRC and auto compile it into this library
add_library(default_animations STATIC ${ANIMATION_QRC})
