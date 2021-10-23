add_library(utils src/utils.c)

target_include_directories(utils PUBLIC include)
target_link_libraries(utils PUBLIC errors)
