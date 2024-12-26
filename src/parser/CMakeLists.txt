add_library(parser_lib lib.cpp tokenizer.cpp parser.cpp)
target_include_directories(parser_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
