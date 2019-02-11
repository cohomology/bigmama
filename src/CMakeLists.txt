list(APPEND BIGMAMA_LIBRARY_SOURCE
  ${CMAKE_SOURCE_DIR}/src/assets.cpp 
  ${CMAKE_SOURCE_DIR}/src/game.cpp 
  ${CMAKE_SOURCE_DIR}/src/bigmama.cpp
)

find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED) 
set(OpenGL_GL_PREFERENCE "GLVND") 

find_package(OpenGL REQUIRED)
find_package(PhysFS REQUIRED)
find_package(Boost COMPONENTS system filesystem REQUIRED)

add_library(bigmamalib ${BIGMAMA_LIBRARY_SOURCE}) 
set_target_properties(bigmamalib PROPERTIES OUTPUT_NAME bigmama)
target_include_directories(bigmamalib PUBLIC 
  ${CMAKE_SOURCE_DIR}/include  
  ${CMAKE_CURRENT_BINARY_DIR}
)

add_executable(bigmama bigmama.cpp)  
target_include_directories(bigmama PUBLIC ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(bigmama 
  sfml-graphics 
  sfml-audio 
  OpenGL::OpenGL 
  ${PHYSFS_LIBRARY} 
  ${Boost_FILESYSTEM_LIBRARY}
  ${Boost_SYSTEM_LIBRARY}
  bigmamalib
)
install (TARGETS bigmama DESTINATION bin)
