cmake_minimum_required(VERSION 3.25)
project(
    boilerc
    VERSION 0.0.1
    DESCRIPTION "Cross-platform C utility library"
    LANGUAGES C
)

add_library(${PROJECT_NAME}
    src/bc_fileio.c
)

target_include_directories(${PROJECT_NAME}
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_compile_features(${PROJECT_NAME}
    PUBLIC
    c_std_23
)

if(MSVC)
    target_compile_options(${PROJECT_NAME}
    PRIVATE
    /W4
    )
else()
    target_compile_options(${PROJECT_NAME}
    PRIVATE
    -Wall
    -Wextra
    -Wpedantic
    )
endif()

add_subdirectory(examples)
