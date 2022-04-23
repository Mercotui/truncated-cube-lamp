# Construct qrc with all website files
file(WRITE
  ${qrc_file}
  "<!DOCTYPE RCC><RCC version=\"1.0\"><qresource prefix=\"/${qrc_prefix}\">\n"
)

foreach(source_file ${source_files})
  message("Adding file to QRC: ${source_file}")
  file(RELATIVE_PATH
    source_file_relative_path
    ${CMAKE_CURRENT_BINARY_DIR} ${source_file}
  )

  file(RELATIVE_PATH
    source_file_short_name
    ${source_files_dir} ${source_file}
  )

  file(APPEND
    ${qrc_file}
    "    <file alias=\"${source_file_short_name}\">"
    "${source_file_relative_path}</file>\n"
  )
endforeach()

file(APPEND ${qrc_file} "</qresource></RCC>\n")
