add_subdirectory(parser)

add_executable(kerang main.cpp)
target_link_libraries(kerang PRIVATE parser_lib)
