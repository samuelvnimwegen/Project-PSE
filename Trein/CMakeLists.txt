cmake_minimum_required(VERSION 3.6)
project(Trein)

set(CMAKE_VERBOSE_MAKEFILE ON)

set(CMAKE_CXX_STANDARD 98)
set(CMAKE_CXX_FLAGS "-std=c++98 -Wall -Werror -O0")
set(CMAKE_EXE_LINKER_FLAGS -pthread)

# Set include dir
include_directories(./gtest/include)
include_directories(./gtest/include)

# Set Library dir
link_directories(./gtest/lib)

# Set source files for RELEASE target
set(RELEASE_SOURCE_FILES Station.cpp Tram.cpp TramSysteem.cpp  main.cpp
        XML/tinyxmlparser.cpp XML/tinystr.cpp XML/tinyxml.cpp XML/tinyxmlerror.cpp)

# Set source files for DEBUG target
set(DEBUG_SOURCE_FILES Station.cpp Tram.cpp TramSysteem.cpp tests.cpp
        XML/tinyxmlparser.cpp XML/tinystr.cpp XML/tinyxml.cpp XML/tinyxmlerror.cpp)

# Create RELEASE target
add_executable(ttt ${RELEASE_SOURCE_FILES})

# Create DEBUG target
add_executable(ttt_debug ${DEBUG_SOURCE_FILES})

# Link library
target_link_libraries(ttt_debug gtest)