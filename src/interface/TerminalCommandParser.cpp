#include "TerminalCommandParser.hpp"
#include "../utilities/termcolor.h"
#include "../system/SystemFileManager.hpp"
#include <sstream>

using namespace std;

namespace qtv {
    void TerminalCommandParser::start() {
        while (true) {
            cout << termcolor::blue << "$ " << termcolor::reset;
            string temp;
            getline(cin, temp);
            stringstream user_input(temp);
            string command, args;
            user_input >> command;
            if (command == "exit") {
                return;
            } else if (command == "cd") {
                user_input >> args;
                SystemFileManager::pwd(args);
            } else if (command == "start") {
                user_input >> args;
                directoryStructure = new ParsedDirectoryStructure("Assignment", nullptr);
                directoryStructure->load(args);
                directoryStructure->validate();
            } else if (command == "pwd") {
                cout << SystemFileManager::pwd() << endl;
            } else if (command == "ls") {
                if (directoryStructure == nullptr) {
                    cout << termcolor::red << "ERROR:" << termcolor::reset
                         << "You have not loaded an assignment" << endl;
                } else {
                    directoryStructure->print();
                }
            } else if (command == "zip") {
                string dest;
                if (!(user_input >> dest)) {
                    dest = "compressed.zip";
                }
                SystemFileManager::zip(directoryStructure->enlist(true), dest);
            } else {
                cout << termcolor::red << "Error:" << termcolor::reset << " Command Does not Exist";
            }
        }
    }
}