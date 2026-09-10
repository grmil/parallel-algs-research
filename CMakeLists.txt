cmake_minimum_required(VERSION 3.28)

project(linalg LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

execute_process(
    COMMAND git describe --tags --always --dirty
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    OUTPUT_VARIABLE GIT_VERSION
    OUTPUT_STRIP_TRAILING_WHITESPACE
)

if(NOT GIT_VERSION)
    set(GIT_VERSION "unknown")
endif()

configure_file(
    ${CMAKE_SOURCE_DIR}/version.h.in
    ${CMAKE_BINARY_DIR}/generated/version.h
)

include(FetchContent)

FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG v1.17.0
)

FetchContent_MakeAvailable(googletest)

add_library(linalg INTERFACE)

target_include_directories(linalg
    INTERFACE
        ${CMAKE_SOURCE_DIR}/src
        ${CMAKE_BINARY_DIR}/generated
)

target_compile_definitions(linalg
    INTERFACE
        APPVERSION="${GIT_VERSION}"
)

add_executable(matvec_example
    examples/matvec.cpp
)

target_link_libraries(matvec_example
    PRIVATE
        linalg
)

enable_testing()

add_executable(linalg_test
    tests/test.cpp
)

target_link_libraries(linalg_test
    PRIVATE
        linalg
        GTest::gtest_main
)

include(GoogleTest)

gtest_discover_tests(linalg_test)

