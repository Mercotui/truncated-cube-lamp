find_package(Qt5 COMPONENTS Core REQUIRED)

set(CMAKE_AUTORCC ON)

# Set libraries file paths
set(LIBRARIES_FILES_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(LIBRARIES_QRC ${CMAKE_CURRENT_BINARY_DIR}/libraries.qrc)
set(LIBRARIES_QRC_PREFIX "libraries")
file(GLOB_RECURSE LIBRARIES_FILES CONFIGURE_DEPENDS ${LIBRARIES_FILES_DIR}/*.js)

# Comand to generate QRC
add_custom_command(
    OUTPUT
        ${LIBRARIES_QRC}
    DEPENDS
        ${LIBRARIES_FILES}
    COMMAND
      ${CMAKE_COMMAND}
      -Dqrc_file=${LIBRARIES_QRC}
      -Dsource_files_dir=${LIBRARIES_FILES_DIR}
      -Dqrc_prefix=${LIBRARIES_QRC_PREFIX}
      "-Dsource_files=${LIBRARIES_FILES}"
      -P ${CMAKE_SOURCE_DIR}/cmake/qrc_generator.cmake
    COMMENT
        "Generating libraries.qrc"
    VERBATIM
)

# Use generated QRC and auto compile it into this library
add_library(js_libraries STATIC ${LIBRARIES_QRC})
