cmake_minimum_required(VERSION 3.5)

project(TagParser)

option(WITH_COVERAGE "add coverage")
if(WITH_COVERAGE)
    add_compile_options(--coverage)
    add_link_options(--coverage)
endif()

option(WITH_SANITIZERS "add sanitizers")
if(WITH_SANITIZERS)
    add_compile_options(-fno-omit-frame-pointer -fsanitize=address)
    add_link_options(-fsanitize=address)
endif()

option(WITH_TESTS "build tests")
if(WITH_TESTS OR WITH_SANITIZERS OR WITH_COVERAGE)
    enable_testing()
    find_package(GTest REQUIRED)
    set(BUILD_TESTS ON)
endif()

add_subdirectory(lib/tag)
add_subdirectory(lib/tag_parser)
add_subdirectory(lib/utils)

