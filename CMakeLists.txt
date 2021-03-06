cmake_minimum_required (VERSION 2.6)
project (8006-asn3)

set (8006-asn3_VERSION_MAJOR 1)
set (8006-asn3_VERSION_MINOR 0)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_CXX_FLAGS "-Wall -Wextra -fsanitze=address")
set(CMAKE_CXX_FLAGS_DEBUG "-g -O0")
set(CMAKE_CXX_FLAGS_RELEASE "-Ofast -s -fno-ident  -march=native -flto -DNDEBUG")


set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_definitions(-D_POSIX_C_SOURCE=200809L)
add_definitions(-D_DEFAULT_SOURCE)

include_directories(src)

file(GLOB MAIN
    "src/*.c"
    "src/*.cpp"
    )

add_executable(8006-asn3 ${MAIN})

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})

target_link_libraries(8006-asn3 rt Threads::Threads ${CURSES_LIBRARIES})
