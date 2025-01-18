find_package(CMocka REQUIRED)

add_executable(test_parser test_parser.c)
target_link_libraries(test_parser PRIVATE parser_lib cmocka)
add_test(NAME test_parser COMMAND test_parser)

add_executable(test_tokenizer test_tokenizer.c)
target_link_libraries(test_tokenizer PRIVATE parser_lib cmocka)
add_test(NAME test_tokenizer COMMAND test_tokenizer)
