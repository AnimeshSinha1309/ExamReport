#ifndef EXAMREPORT_DOCUMENT_STRUCTURE_EXCEPTION_H
#define EXAMREPORT_DOCUMENT_STRUCTURE_EXCEPTION_H

#include <exception>
#include <string>

using namespace std;

namespace qtv {

    class DocumentStructureException : std::exception {
    public:
        string reason;
        int line;

        DocumentStructureException(string reason, int line);

        string what();
    };

}

#endif //EXAMREPORT_DOCUMENT_STRUCTURE_EXCEPTION_H
