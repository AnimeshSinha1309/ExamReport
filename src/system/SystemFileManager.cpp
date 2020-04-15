#include <iostream>
#include <unistd.h>
#include "SystemFileManager.hpp"

using namespace std;

void SystemFileManager::zip(const string &files, const string &output) {
    string command = "zip " + output + " " + files;
    system(command.c_str());
}

void SystemFileManager::pwd(const string &dir) {
    chdir(dir.c_str());
    system("pwd");
}
