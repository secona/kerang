find_package(GTest REQUIRED)

add_executable(kerang_tests test_parser.cpp test_tokenizer.cpp)
target_link_libraries(kerang_tests PRIVATE parser_lib gtest gtest_main)
add_test(NAME my_tests COMMAND kerang_tests)
