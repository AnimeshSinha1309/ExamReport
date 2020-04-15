cmake_minimum_required(VERSION 3.13)
project(ExamReport)

set(CMAKE_CXX_STANDARD 14)

include_directories(src/structure)

add_executable(ExamReport
        src/interface/main.cpp
        src/structure/ParsedDirectoryStructure.hpp
        src/structure/ParsedDirectoryStructure.cpp
        src/system/SystemFileManager.hpp
        src/system/SystemFileManager.cpp
        src/exceptions/DocumentStructureException.hpp
        src/exceptions/DocumentStructureException.cpp
        src/utilities/termcolor.h)

target_link_libraries(ExamReport
        crypto ssl)