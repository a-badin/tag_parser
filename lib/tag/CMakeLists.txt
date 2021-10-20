add_library(tag src/tag.c
                src/attribute.c)

target_include_directories(tag PUBLIC include)
target_link_libraries(tag PUBLIC utils)

if(BUILD_TESTS)
    add_subdirectory(tests)
endif()
