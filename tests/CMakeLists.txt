find_package(GTest REQUIRED)

add_executable(kerang_tests test_tokenizer.cpp)
target_link_libraries(kerang_tests PRIVATE gtest gtest_main)
add_test(NAME my_tests COMMAND kerang_tests)
