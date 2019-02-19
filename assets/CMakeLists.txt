find_package(SevenZip REQUIRED)

list(APPEND BIGMAMA_RESOURCE_FILES
  ${CMAKE_SOURCE_DIR}/assets/stone_brick1.png   
  ${CMAKE_SOURCE_DIR}/assets/stone_brick2.png    
  ${CMAKE_SOURCE_DIR}/assets/level_edit_frame.png  
  ${CMAKE_SOURCE_DIR}/assets/skull.png  
  ${CMAKE_SOURCE_DIR}/assets/coin.png   

  ${CMAKE_SOURCE_DIR}/assets/FreeMono.ttf 
  ${CMAKE_SOURCE_DIR}/assets/template.json 
  ${CMAKE_SOURCE_DIR}/assets/level1.json

  ${CMAKE_BINARY_DIR}/translations/bigmama_en.qm
  ${CMAKE_BINARY_DIR}/translations/bigmama_de.qm 
)

add_custom_command(OUTPUT bigmama.pak
                   DEPENDS ${BIGMAMA_RESOURCE_FILES} translations
                   COMMAND ${SEVENZIP_BIN} a ${CMAKE_CURRENT_BINARY_DIR}/bigmama.pak ${BIGMAMA_RESOURCE_FILES})

add_executable(bin2c bin2c.cpp)   

add_custom_target(bigmama.pak.trg ALL DEPENDS bigmama.pak ${BIGMAMA_RESOURCE_FILES})
