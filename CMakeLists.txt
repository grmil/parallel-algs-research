cmake_minimum_required(VERSION 3.20)

project(linalg LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(linalg_serial
    src/serial/vector.cpp
)

target_include_directories(linalg_serial
    PUBLIC
	${CMAKE_SOURCE_DIR}/include
)

#add_executable(demo_matvec examples/demo_matvec.cpp)
#target_link_libraries(demo_matvec PRIVATE linalg_serial)
