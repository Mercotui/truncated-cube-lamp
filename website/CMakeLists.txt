find_package(Qt6 COMPONENTS Core REQUIRED)

set(CMAKE_AUTORCC ON)

# Set website file paths
set(website_files_dir ${CMAKE_SOURCE_DIR}/website)
set(website_qrc ${CMAKE_CURRENT_BINARY_DIR}/website.qrc)
file(GLOB_RECURSE website_files CONFIGURE_DEPENDS ${website_files_dir}/*)

# Comand to generate QRC
add_custom_command(
    OUTPUT
        ${website_qrc}
    DEPENDS
        ${website_files}
    COMMAND
      ${CMAKE_COMMAND} -Dwebsite_qrc=${website_qrc} -Dwebsite_files_dir=${website_files_dir} "-Dwebsite_files=${website_files}" -P ${CMAKE_SOURCE_DIR}/cmake/website_qrc_generator.cmake
    COMMENT
        "Generating website.qrc"
    VERBATIM
)

# Use generated QRC and auto compile it into this library
add_library(website ${website_qrc})
