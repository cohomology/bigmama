add_executable(bigmama assets.cpp bigmama.cpp)
find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED) 
set(OpenGL_GL_PREFERENCE "GLVND") 
find_package(OpenGL REQUIRED)
find_package(PhysFS REQUIRED)
target_include_directories(bigmama ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(bigmama sfml-graphics sfml-audio OpenGL::OpenGL ${PHYSFS_LIBRARY})

