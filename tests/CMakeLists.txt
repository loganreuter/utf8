cmake_minimum_required(VERSION 3.14)

project(
    Tests
    VERSION 0.1
    DESCRIPTION "Testing for UTF-8 Library"
    LANGUAGES C
)

file(GLOB LIB_SOURCES ../src/*.c)
file(GLOB LIB_HEADERS ../src/*.h)

file(GLOB SRC *.c)
file(GLOB HEADERS *.h)

add_library(UTF_LIB ${LIB_SOURCES} ${LIB_HEADERS})

add_executable(test ${SRC} ${HEADERS})

target_link_libraries(test PUBLIC UTF_LIB)