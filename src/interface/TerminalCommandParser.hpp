#ifndef EXAMREPORT_TERMINAL_COMMAND_PARSER_H
#define EXAMREPORT_TERMINAL_COMMAND_PARSER_H

#include "../structure/ParsedDirectoryStructure.hpp"

namespace qtv {
    class TerminalCommandParser {
    public:
        ParsedDirectoryStructure *directoryStructure = nullptr;

        void start();
    };
}

#endif //EXAMREPORT_TERMINAL_COMMAND_PARSER_H
