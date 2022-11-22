cmake_minimum_required(VERSION 3.23)
project(cpp_primer)

set(CMAKE_CXX_STANDARD 11)

add_executable(cpp_primer main.cpp 12.3/main.cpp 12.3/TextQuery.h 12.3/QueryResult.h)
