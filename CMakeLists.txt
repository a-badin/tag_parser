cmake_minimum_required(VERSION 3.5)

project(TagParser)

#include_directories(/usr/local/Cellar/googletest/1.11.0/include)
option(BUILD_TESTS "build tests")
if(BUILD_TESTS)
    enable_testing()
    find_package(GTest REQUIRED)
endif()

add_subdirectory(lib/tag)


#add_subdirectory(lib/tag_parser)

#add_executable(tag_parser src/main.c)
#target_link_libraries(tag_parser lib_tag_parser)

