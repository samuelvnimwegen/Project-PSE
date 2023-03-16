cmake_minimum_required(VERSION 3.23)
project(Trein)

add_executable(Trein main.cpp Tram.cpp  Station.cpp TramSysteem.cpp XML/tinystr.cpp XML/tinyxml.cpp XML/tinyxmlerror.cpp XML/tinyxmlparser.cpp tests.cpp)

set(CMAKE_CXX_STANDARD 98)
set(CMAKE_CXX_FLAGS "-std=c++98 -Wall -Werror -O0")
set(CMAKE_EXE_LINKER_FLAGS -pthread)

# Set include dir
include_directories(./gtest/include)

# Set Library dir
link_directories(./gtest/lib)

# Set source files for RELEASE target
set(RELEASE_SOURCE_FILES tramsysteem.cpp)

# Set source files for DEBUG target
set(DEBUG_SOURCE_FILES tramsysteem.cpp)

# Create RELEASE target
add_executable(ttt ${RELEASE_SOURCE_FILES})

# Create DEBUG target
add_executable(ttt_debug ${DEBUG_SOURCE_FILES})

# Link library
target_link_libraries(ttt_debug gtest)