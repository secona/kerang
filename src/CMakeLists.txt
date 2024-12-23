add_subdirectory(parser)
add_subdirectory(commands)

add_executable(kerang main.cpp)

target_link_libraries(kerang PRIVATE parser_lib)
target_link_libraries(kerang PRIVATE commands_lib)
target_include_directories(kerang PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
