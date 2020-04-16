#include <iostream>
#include "../structure/ParsedDirectoryStructure.hpp"
#include "../system/SystemFileManager.hpp"
using namespace std;
using namespace qtv;

int main() {
    ParsedDirectoryStructure tree("Assignment 1", nullptr);
    tree.load("../examples/1_assignment/structure.qtv");
    SystemFileManager::pwd("../examples/1_solution/");
    tree.validate();
    tree.print();
    SystemFileManager::zip(tree.enlist(true), "compressed.zip");
}