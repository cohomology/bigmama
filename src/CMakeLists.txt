add_custom_command(OUTPUT bigmama.pak.cpp
  DEPENDS bigmama.pak.trg bin2c ${CMAKE_CURRENT_BINARY_DIR}/../assets/bigmama.pak  
  COMMAND ${CMAKE_CURRENT_BINARY_DIR}/../assets/bin2c ${CMAKE_CURRENT_BINARY_DIR}/../assets/bigmama.pak 
          ${CMAKE_CURRENT_BINARY_DIR}/bigmama.pak.cpp)

add_custom_target(bigmama.pak.cpp.trg ALL DEPENDS bigmama.pak.cpp)  

find_package(Qt5Widgets REQUIRED)
find_package(PhysFS REQUIRED) 

list (APPEND BIGMAMALEVEL_SOURCE 
  ${PROJECT_SOURCE_DIR}/src/level_editor.cpp
  ${PROJECT_SOURCE_DIR}/src/file_system.cpp 
  ${PROJECT_SOURCE_DIR}/src/translation_scope.cpp  
)

list (APPEND BIGMAMALEVEL_QOBJECT_HEADERS
  ${PROJECT_SOURCE_DIR}/include/level_editor.h
)

qt5_wrap_cpp(BIGMAMALEVEL_HEADERS_MOC ${BIGMAMALEVEL_QOBJECT_HEADERS})

add_library(leveleditor STATIC
  ${BIGMAMALEVEL_SOURCE}
  ${BIGMAMALEVEL_HEADERS_MOC}
  ${BIGMAMA_QM}
)

add_dependencies(leveleditor bigmama.pak.cpp.trg) 
target_include_directories(leveleditor PUBLIC 
  ${CMAKE_SOURCE_DIR}/include   
  ${CMAKE_CURRENT_BINARY_DIR} 
  ${PHYSFS_INCLUDE_DIR}  
)
target_link_libraries (leveleditor Qt5::Widgets)

add_executable(bigmamalevel bigmamalevel.cpp)
target_link_libraries (bigmamalevel 
  leveleditor
  ${PHYSFS_LIBRARY}
)
target_include_directories(bigmamalevel PUBLIC
  ${CMAKE_SOURCE_DIR}/include   
)
