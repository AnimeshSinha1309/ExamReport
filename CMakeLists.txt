cmake_minimum_required(VERSION 3.13)
project(ExamReport)

set(CMAKE_CXX_STANDARD 14)

include_directories(src/structure)

add_executable(ExamReport
        src/structure/main.cpp
        src/structure/parse.cpp
        src/structure/parse.hpp
        src/exceptions/DocumentStructureException.h
        src/exceptions/DocumentStructureException.cpp
        )
