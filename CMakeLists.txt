cmake_minimum_required(VERSION 3.10)
project(ExamReport)

set(CMAKE_CXX_STANDARD 17)

include_directories(src/)

add_compile_options(-Wall -Wextra -Wpedantic)

add_executable(${PROJECT_NAME}
        src/interface/main.cpp
        src/structure/ParsedDirectoryStructure.hpp
        src/structure/ParsedDirectoryStructure.cpp
        src/system/SystemFileManager.hpp
        src/system/SystemFileManager.cpp
        src/exceptions/DocumentStructureException.hpp
        src/exceptions/DocumentStructureException.cpp
        src/interface/TerminalCommandParser.hpp
        src/interface/TerminalCommandParser.cpp
        src/utilities/termcolor.h)

target_link_libraries(ExamReport
        crypto ssl)

install(TARGETS ${PROJECT_NAME} DESTINATION bin)
install(DIRECTORY examples DESTINATION examples)
