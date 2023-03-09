cmake_minimum_required(VERSION 3.23)
project(Trein)

set(CMAKE_CXX_STANDARD 14)

add_executable(Trein main.cpp Tram.cpp  Station.cpp TramSysteem.cpp XML/tinystr.cpp XML/tinyxml.cpp XML/tinyxmlerror.cpp XML/tinyxmlparser.cpp)

