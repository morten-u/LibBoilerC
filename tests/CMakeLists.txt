add_executable(test_fileio
    test_fileio.c
)

target_link_libraries(test_fileio
    PRIVATE
    boilerc
)

add_test(
    NAME fileio
    COMMAND test_fileio
)
