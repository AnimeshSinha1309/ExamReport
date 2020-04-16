#ifndef EXAMREPORT_PARSED_DIRECTORY_STRUCTURE_H
#define EXAMREPORT_PARSED_DIRECTORY_STRUCTURE_H

#include <string>
#include <vector>

using namespace std;

namespace qtv {

    class ParsedDirectoryStructure {
    private:
        ParsedDirectoryStructure *parent;
        vector<ParsedDirectoryStructure *> files;

        bool submit = true;
        bool distribution = false;
        bool exists = false;

        string path = "";
        string md5sum = "";

    public:
        string name;

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
         * Generates the MD5 sum of the entire tree, and returns the net MD5 sum
         * of the full directory.
         * @param: string root - The root file path of the subdirectory to hash
         * @returns: string hash - The MD5 hash of the subdirectory
         */
        string validate();

        /**
         * Generates the list of all files in a directory, allows selection of
         * which files need to be included.
         * @param: string submittable - Selects files that need to be submitted
         *         only if set to true, removes this constraint if false
         * @returns: string files - A string listing out all files
         */
        string enlist(bool submittable_only = false);

        /**
         * Prints the File Structure tree that is loading in the current object
         * @param: int depth - nesting depth of the current file
         */
        void print(int depth = 0);
    };

}  // namespace qtv

#endif  // EXAMREPORT_PARSED_DIRECTORY_STRUCTURE_H
