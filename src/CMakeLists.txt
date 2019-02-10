add_executable(bigmama bigmama.cpp)
find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED) 
set(OpenGL_GL_PREFERENCE "GLVND") 
find_package(OpenGL REQUIRED)
target_link_libraries(bigmama sfml-graphics sfml-audio OpenGL::OpenGL)

