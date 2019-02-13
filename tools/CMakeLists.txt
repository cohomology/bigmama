find_package(PNG REQUIRED)

add_executable(png2json png2json.cpp)   
target_include_directories(png2json PUBLIC ${PNG_INCLUDE_DIRS})
target_link_libraries(png2json ${PNG_LIBRARIES})


