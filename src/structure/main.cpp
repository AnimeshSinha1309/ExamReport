#include <iostream>
#include "ParsedDirectoryStructure.hpp"

using namespace std;
using namespace qtv;

int main() {
    ParsedDirectoryStructure tree("Assignment 1", nullptr);
    tree.load("../examples/1_assignment/structure.qtv");
    tree.validate("../examples/1_solution");
    tree.print();
}