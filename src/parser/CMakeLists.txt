add_library(parser_lib tokenizer.c parser.c)
target_include_directories(parser_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
