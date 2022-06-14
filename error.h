#ifndef ERROR_H
#define ERROR_H

#include <jsontoken.h>
#include <iostream>
#include <sstream>

class err
{
public:
    err();
    err(int index, const std::string & error);
    err(int index, const std::string & error, std::shared_ptr<std::string> source);
    err(int index, const std::string & error, JSONToken token);
    std::string formatParseError();
    std::string formatError();
    std::string getBase();
    int getIndex();
    void setIndexAndBase(int index,  const std::string &error);
    void setError(const std::string & base, int index);
    void setError();
    void setParseError(const std::string & base, JSONToken token);
    static std::string JSONTokenTypeToString(JSONTokenType jtt);
private:
    int index;
    std::string whitespace;
    std::string lastline;
    std::string tokenValue;
    std::string tokenType;
    std::string base;
    std::shared_ptr<std::string> source;
    int line;
    int column;
    void appendToLineAndSpace(char c, bool &rFlag);
};


#endif // ERROR_H
