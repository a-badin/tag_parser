add_library(tag_parser src/tag_parser.c)
target_include_directories(tag_parser PUBLIC include)

target_link_libraries(tag_parser PUBLIC tag)
