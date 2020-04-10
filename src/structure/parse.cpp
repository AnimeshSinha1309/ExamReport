#include <utility>

#include "parse.hpp"
#include "../exceptions/DocumentStructureException.h"

#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;

namespace qtv {

    ParsedDirectoryStructure::ParsedDirectoryStructure(string n,
                                                       ParsedDirectoryStructure *p)
            : name(std::move(n)), parent(p) {
        files = vector<ParsedDirectoryStructure *>(0);
        files.reserve(4);
    }

    void ParsedDirectoryStructure::load(const string &filename) {
        ifstream file(filename);
        if (!file.is_open()) {
            throw DocumentStructureException("could not find the file", 0);
        }

        string data, symbol;
        int previous_depth = 0;
        ParsedDirectoryStructure *current = nullptr;

        // Handling Line 1
        getline(file, data);
        if (data[0] != '.')
            throw DocumentStructureException("Line 0 does not start with a `.`", 0);
        current = this;

        for (int line = 2; getline(file, data); line++) {
            stringstream s(data);
            // Phase 1, | | | +-- directory nesting parser
            int depth = 1;
            while (s >> symbol && symbol == "|")
                depth++;
            if (symbol != "+--")
                throw DocumentStructureException("the structure of line is not `| | | +--` on line ", line);
            // Phase 2, get the filename and attach node
            s >> symbol;
            if (depth > previous_depth + 1) {
                throw DocumentStructureException("sudden increase in nesting depth on line ", line);
            }
            while (previous_depth != depth - 1) {
                current = current->parent;
                previous_depth--;
            }
            ParsedDirectoryStructure *incoming = new ParsedDirectoryStructure(symbol, current);
            current->files.push_back(incoming);
            current = incoming;
            previous_depth = depth;
            // Phase 3, get the options right
            while (s >> symbol) { ;
            }
        }
    }

    void ParsedDirectoryStructure::print(int depth) {
        if (depth != 0) {
            for (int i = 0; i < depth - 1; i++) cout << "|  ";
            cout << "+-- ";
        } else {
            cout << ". ";
        }
        cout << this->name << endl;
        for (auto child : this->files) child->print(depth + 1);
    }

};  // namespace qtv