add_executable(kerang main.cpp builtins.cpp)

target_include_directories(kerang PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
