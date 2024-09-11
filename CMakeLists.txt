cmake_minimum_required(VERSION 3.0)
project(DXVLSCRXPT)

file(GLOB_RECURSE SOURCES "src/*.cpp")

add_executable(dxvlscrxpt ${SOURCES})
