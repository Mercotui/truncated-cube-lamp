# Construct qrc with all website files
file(WRITE
  ${website_qrc}
  "<!DOCTYPE RCC><RCC version=\"1.0\"><qresource prefix=\"/website\">\n"
)

foreach(website_file ${website_files})
  message("Adding to website QRC: ${website_file}")
  file(RELATIVE_PATH
    website_file_relative_path
    ${CMAKE_CURRENT_BINARY_DIR} ${website_file}
  )

  file(RELATIVE_PATH
    website_file_short_name
    ${website_files_dir} ${website_file}
  )

  file(APPEND
    ${website_qrc}
    "    <file alias=\"${website_file_short_name}\">"
    "${website_file_relative_path}</file>\n"
  )
endforeach()
file(APPEND ${website_qrc} "</qresource></RCC>\n")
