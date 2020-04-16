#ifndef EXAMREPORT_SYSTEM_FILE_MANAGER_H
#define EXAMREPORT_SYSTEM_FILE_MANAGER_H

#include <string>

using namespace std;

class SystemFileManager {
    const string OPERATING_SYSTEM = "Linux";

public:

    /**
     * Zips all the files that need to be submitted in the file subtree
     * @param: string output - specifies the name of the output file
     */
    static void zip(const string &files, const string &output = "compressed.zip");

    /**
     * Sets the present working directory
     * @param: string dir - required working directory
     */
    static void pwd(const string &dir);;
};


#endif //EXAMREPORT_SYSTEM_FILE_MANAGER_H
