add_library(commands_lib lib.cpp builtins.cpp)
target_include_directories(commands_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
