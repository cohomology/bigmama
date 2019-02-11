list(APPEND BIGMAMA_LIBRARY_SOURCE
  ${CMAKE_SOURCE_DIR}/src/assets.cpp 
  ${CMAKE_SOURCE_DIR}/src/game.cpp 
  ${CMAKE_SOURCE_DIR}/src/level.cpp 
)

find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED) 
set(OpenGL_GL_PREFERENCE "GLVND") 

find_package(OpenGL REQUIRED)
find_package(PhysFS REQUIRED)
find_package(JsonCpp REQUIRED)
find_package(Boost REQUIRED)

add_custom_command(OUTPUT bigmama.pak.cpp
  DEPENDS bigmama.pak.trg bin2c ${CMAKE_CURRENT_BINARY_DIR}/../assets/bigmama.pak  
  COMMAND ${CMAKE_CURRENT_BINARY_DIR}/../assets/bin2c ${CMAKE_CURRENT_BINARY_DIR}/../assets/bigmama.pak 
          ${CMAKE_CURRENT_BINARY_DIR}/bigmama.pak.cpp)

add_custom_target(bigmama.pak.cpp.trg ALL DEPENDS bigmama.pak.cpp)  

add_library(bigmamalib ${BIGMAMA_LIBRARY_SOURCE})
add_dependencies(bigmamalib bigmama.pak.cpp.trg)
set_target_properties(bigmamalib PROPERTIES OUTPUT_NAME bigmama)
target_include_directories(bigmamalib PUBLIC 
  ${CMAKE_SOURCE_DIR}/include  
  ${CMAKE_CURRENT_BINARY_DIR}
  ${JSONCPP_INCLUDE_DIRS}
  ${OPENGL_INCLUDE_DIR}
  ${SFML_INCLUDE_DIR}
  ${PHYSFS_INCLUDE_DIR}
  ${BOOST_INCLUDE_DIRS}
)

add_executable(bigmama bigmama.cpp)  
target_include_directories(bigmama PUBLIC ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(bigmama 
  sfml-graphics 
  sfml-audio 
  OpenGL::OpenGL 
  ${PHYSFS_LIBRARY} 
  bigmamalib
  ${JSONCPP_LIBRARY}
)
install (TARGETS bigmama DESTINATION bin)
