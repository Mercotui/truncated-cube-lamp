find_package(Qt5 COMPONENTS Core REQUIRED)

set(CMAKE_AUTORCC ON)

# Set website file paths
set(WEBSITE_FILES_DIR ${CMAKE_SOURCE_DIR}/website/dist)
set(WEBSITE_QRC ${CMAKE_CURRENT_BINARY_DIR}/website.qrc)
set(WEBSITE_QRC_PREFIX "website")
file(GLOB_RECURSE WEBSITE_FILES CONFIGURE_DEPENDS ${WEBSITE_FILES_DIR}/*)

# Comand to generate QRC
add_custom_command(
    OUTPUT
        ${WEBSITE_QRC}
    DEPENDS
        ${WEBSITE_FILES}
    COMMAND
      ${CMAKE_COMMAND}
      -Dqrc_file=${WEBSITE_QRC}
      -Dsource_files_dir=${WEBSITE_FILES_DIR}
      -Dqrc_prefix=${WEBSITE_QRC_PREFIX}
      "-Dsource_files=${WEBSITE_FILES}"
      -P ${CMAKE_SOURCE_DIR}/cmake/qrc_generator.cmake
    COMMENT
        "Generating website.qrc"
    VERBATIM
)

# Use generated QRC and auto compile it into this library
add_library(website STATIC ${WEBSITE_QRC})
