#ifndef LOGIC_H
#define LOGIC_H

#include <parser.h>
#include <lexer.h>
#include <deparser.h>
#include <error.h>

enum class FuncType{
    readFile,
    parse,
    deparse
};

class app
{
public:
    app();
    void  readFile(const std::string &  pathFileName);
    void parse(const std::string &source);
    void  entryPoint(FuncType ft, const std::string &fa);
    void entryPoint(FuncType ft, JSONValue fa);
    std::string getFile();
    std::string getError();
    std::string getJsonStr();
private:
    std::string file;
    std::string jsonStr;
    err error;
};

#endif // LOGIC_H
