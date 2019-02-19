find_package(Qt5Widgets)

list (APPEND BIGMAMALEVEL_SOURCE 
  ${PROJECT_SOURCE_DIR}/src/level_editor.cpp
)

list (APPEND BIGMAMALEVEL_HEADERS
  ${PROJECT_SOURCE_DIR}/include/level_editor.h
)

qt5_wrap_cpp(BIGMAMALEVEL_HEADERS_MOC ${BIGMAMALEVEL_HEADERS})

add_library(leveleditor SHARED 
  ${BIGMAMALEVEL_SOURCE}
  ${BIGMAMALEVEL_HEADERS_MOC}
)
target_include_directories(leveleditor PUBLIC 
  ${CMAKE_SOURCE_DIR}/include   
)
target_link_libraries (leveleditor Qt5::Widgets)

add_executable(bigmamalevel bigmamalevel.cpp)
target_link_libraries (bigmamalevel leveleditor)
