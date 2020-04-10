#ifndef EXAMREPORT_PARSED_DIRECTORY_STRUCTURE_H
#define EXAMREPORT_PARSED_DIRECTORY_STRUCTURE_H

#include <openssl/md5.h>

#include <string>
#include <vector>

using namespace std;

namespace qtv {

    class ParsedDirectoryStructure {
        ParsedDirectoryStructure *parent;

    public:
        string name;
        vector<ParsedDirectoryStructure *> files;
        int nesting_depth;

        bool submit = true;
        bool distribution = false;

        /**
         * Loads the directory information from the provided source filename and
         * makes a Abstract Tree out of it.
         * @param: string n - Name of the file or directory of the current
         * object
         * @returns: ParsedDirectoryStructure* p - The parent of the directory
         * or file, nullptr if root
         */
        ParsedDirectoryStructure(string n, ParsedDirectoryStructure *p);

        /**
         * Loads the directory information from the provided source filename and
         * makes a Abstract Tree out of it.
         * @param: string filename - Name of the file which holds the directory
         * information
         * @returns: ParsedDirectoryStructure* root - Root of the file structure
         * tree loaded form the source file.
         */
        void load(const string &filename);

        /**
         * Prints the File Structure tree that is loading in the current object
         */
        void print(int depth);
    };

};  // namespace qtv

#endif  // EXAMREPORT_PARSED_DIRECTORY_STRUCTURE_H
