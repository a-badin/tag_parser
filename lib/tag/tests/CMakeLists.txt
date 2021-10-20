add_executable(tag_test src/test_attribute.cpp
                        src/test_tag.cpp)

target_link_libraries(tag_test tag GTest::gtest_main)
add_test(NAME tag_test COMMAND tag_test)
