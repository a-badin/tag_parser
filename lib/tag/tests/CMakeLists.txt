add_executable(tag_lib_test src/test_attribute.cpp
                            src/test_tag.cpp)

target_link_libraries(tag_lib_test lib_tag GTest::gtest_main)
add_test(NAME tag_lib_test COMMAND tag_lib_test)
