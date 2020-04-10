#include <iostream>
#include "parse.hpp"

using namespace std;
using namespace qtv;

int main() {
    ParsedDirectoryStructure tree("Assignment 1", nullptr);
    tree.load("../examples/1_assignment/structure.qtv");
    tree.print(0);
}