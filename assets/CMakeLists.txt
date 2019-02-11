find_package(SevenZip REQUIRED)

list(APPEND BIGMAMA_RESOURCE_FILES
  ${CMAKE_SOURCE_DIR}/assets/stone_grey.png
)

add_custom_command(OUTPUT bigmama.pak
                   DEPENDS ${BIGMAMA_RESOURCE_FILES}
                   COMMAND ${SEVENZIP_BIN} a bigmama.pak ${BIGMAMA_RESOURCE_FILES})

add_custom_target(assets ALL DEPENDS bigmama.pak)
