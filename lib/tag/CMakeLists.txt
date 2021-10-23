add_library(tag src/tag.c
                src/attribute.c)

target_include_directories(tag PUBLIC include) # Тот кто залинкуется с tag получит заголовки

target_link_libraries(tag PRIVATE utils # utils используется только в реализации библиотеки, остальным не нужна
                          PUBLIC errors) # Для обработки ошибок всем

if(BUILD_TESTS)
    add_subdirectory(tests)
endif()
