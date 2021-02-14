cmake_minimum_required(VERSION 3.0)
project(cggrt)

set(CMAKE_C_COMPILER clang)
set(CMAKE_C_FLAGS "-std=c99 -Wall -Wextra -Werror")
set(CMAKE_C_FLAGS_DEBUG "-O0 -g3")
set(CMAKE_C_FLAGS_RELEASE "-O3 -DNDEBUG")

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)



#include_directories(SYSTEM "./extern/Catch2/single_include")

include_directories("./include")

add_subdirectory(src)

#Test code
#enable_testing()

#add_custom_target(build-tests)
#add_custom_target(check
#  COMMAND ctest
#  DEPENDS build-tests  
#)
