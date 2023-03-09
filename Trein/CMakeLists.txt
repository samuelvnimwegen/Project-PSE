cmake_minimum_required(VERSION 3.23)
project(Trein)

set(CMAKE_CXX_STANDARD 14)

add_executable(Trein main.cpp Tram.cpp Tram.h Station.cpp Station.h TramSysteem.cpp TramSysteem.h XML/tinyxml.h)

