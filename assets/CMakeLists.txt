find_package(SevenZip REQUIRED)

list(APPEND BIGMAMA_RESOURCE_FILES
  ${CMAKE_SOURCE_DIR}/assets/stone_grey.png
)

add_custom_command(OUTPUT bigmama.pak
                   DEPENDS ${BIGMAMA_RESOURCE_FILES}
                   COMMAND ${SEVENZIP_BIN} a bigmama.pak ${BIGMAMA_RESOURCE_FILES})

set_source_files_properties(
  ${CMAKE_CURRENT_BINARY_DIR}/bigmama.pak
  PROPERTIES GENERATED TRUE
) 

add_executable(bin2c bin2c.cpp)   

add_custom_target(bigmama.pak.trg ALL DEPENDS bigmama.pak)

add_custom_command(OUTPUT bigmama.pak.cpp
                   DEPENDS bigmama.pak.trg bin2c
                   COMMAND ${CMAKE_CURRENT_BINARY_DIR}/bin2c ${CMAKE_CURRENT_BINARY_DIR}/bigmama.pak 
                           ${CMAKE_CURRENT_BINARY_DIR}/../src/bigmama.pak.cpp)

add_custom_target(bigmama.pak.cpp.trg ALL DEPENDS bigmama.pak.cpp) 

