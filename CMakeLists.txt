cmake_minimum_required(VERSION 3.13)

project(TagParser)

add_compile_options(-Wall -Wextra -pedantic)

option(WITH_COVERAGE "Add coverage estimation")
if(WITH_COVERAGE)
    add_compile_options(--coverage)
    add_link_options(--coverage)
endif()

option(WITH_SANITIZERS "Add address sanitizer")
if(WITH_SANITIZERS)
    add_compile_options(-fno-omit-frame-pointer -fsanitize=address)
    add_link_options(-fsanitize=address)
endif()

option(WITH_TESTS "Build tests" ON)
if(WITH_TESTS OR WITH_SANITIZERS OR WITH_COVERAGE)
    enable_testing()
    find_package(GTest REQUIRED)
    set(BUILD_TESTS ON)
endif()

add_subdirectory(lib/tag)
add_subdirectory(lib/tag_parser)
add_subdirectory(lib/utils)
add_subdirectory(lib/errors)

add_executable(main src/main.c)
target_link_libraries(main tag_parser)
