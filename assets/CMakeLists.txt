find_package(SevenZip REQUIRED)

list(APPEND BIGMAMA_RESOURCE_FILES
  ${CMAKE_SOURCE_DIR}/assets/stone_grey.png
)

add_custom_command(OUTPUT bigmama.pak
                   DEPENDS ${BIGMAMA_RESOURCE_FILES}
                   COMMAND ${SEVENZIP_BIN} a bigmama.pak ${BIGMAMA_RESOURCE_FILES})

set_source_files_properties(
  ${CMAKE_CURRENT_BINARY_DIR}/assets/bigmama.pak
  PROPERTIES GENERATED TRUE
) 

add_custom_target(assets ALL DEPENDS bigmama.pak)

install(FILES ${CMAKE_CURRENT_BINARY_DIR}/bigmama.pak  DESTINATION share/bigmama)
