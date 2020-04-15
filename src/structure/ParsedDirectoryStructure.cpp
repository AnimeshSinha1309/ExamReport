#include <utility>

#include "ParsedDirectoryStructure.hpp"
#include "../exceptions/DocumentStructureException.hpp"
#include "../utilities/termcolor.h"

#include <fstream>
#include <sstream>
#include <openssl/md5.h>
#include <iomanip>

using namespace std;

namespace qtv {

    ParsedDirectoryStructure::ParsedDirectoryStructure(string n,
                                                       ParsedDirectoryStructure *p = nullptr)
            : name(std::move(n)), parent(p) {
        files = vector<ParsedDirectoryStructure *>(0);
        files.reserve(4);
        if (p != nullptr) {
            path = p->path + "/" + name;
        } else {
            path = ".";
        }
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
            while (s >> symbol) {
                if (symbol == "(dist)") {
                    incoming->distribution = true;
                } else if (symbol == "(no-submit)") {
                    incoming->submit = false;
                }
            }
        }
        file.close();
    }

    void ParsedDirectoryStructure::print(int depth) {
        if (depth != 0) {
            for (int i = 0; i < depth - 1; i++) cout << "|  ";
            cout << "+-- ";
        } else {
            cout << ". ";
        }
        if (!exists && submit) cout << termcolor::red << this->name << termcolor::reset;
        else if (this->submit) cout << termcolor::green << this->name << termcolor::reset;
        else cout << this->name;
        cout << " (" << this->md5sum << ")";
        if (!this->submit) cout << " (no-submit)";
        if (this->distribution) cout << " (dist)";
        cout << endl;
        for (auto child : this->files) child->print(depth + 1);
    }

    string ParsedDirectoryStructure::validate() {
        MD5_CTX md5Context;
        MD5_Init(&md5Context);
        if (this->files.empty()) {
            ifstream file(path);
            char buf[1024 * 16];
            if (file.is_open()) this->exists = true;
            while (file.good()) {
                file.read(buf, sizeof(buf));
                MD5_Update(&md5Context, buf, file.gcount());
            }
        } else {
            this->exists = true;
            for (ParsedDirectoryStructure *file : this->files) {
                string subHash = file->validate();
                MD5_Update(&md5Context, subHash.c_str(), subHash.size());
                this->exists = this->exists && (file->exists || !file->submit);
            }
        }
        unsigned char result[MD5_DIGEST_LENGTH];
        MD5_Final(result, &md5Context);
        std::stringstream md5string;
        md5string << std::hex << std::uppercase << std::setfill('0');
        for (const auto &byte: result)
            md5string << std::setw(2) << (int) byte;
        this->md5sum = md5string.str();
        return this->md5sum;
    }

    string ParsedDirectoryStructure::enlist(bool submittable_only) {
        if (submittable_only && !submit) {
            return "";
        }
        if (files.empty()) {
            if (exists) {
                return path + " ";
            } else {
                cout << "Warning: Submittable file does not exist - " << path << endl;
                return "";
            }
        } else {
            string result;
            for (auto child : files) {
                result += child->enlist(submittable_only);
            }
            return result;
        }
    }

};  // namespace qtv