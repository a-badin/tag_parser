add_library(lib_tag src/tag.c
                    src/attribute.c
                    src/utils.c)

target_include_directories(lib_tag PUBLIC include)

if(BUILD_TESTS)
    add_subdirectory(tests)
endif()
