#ifndef DEPARSER_H
#define DEPARSER_H


#include <jsonvalue.h>

class deparser
{
public:
    deparser();
    static std::string deparse(JSONValue v, std::string whitespace = "");
};

#endif // DEPARSER_H
