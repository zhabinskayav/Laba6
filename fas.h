#ifndef FAS_H
#define FAS_H
#include <logic.h>
#include <file.h>
#include <parser.h>
#include <deparser.h>
#include <lexer.h>
#include <error.h>
#include <memory.h>

class fas
{
public:
    fas(app my_AP);
    void parseAll(const std::string &pathFileName);
    std::string getError();
    std::string getJson();
    std::string getText();
    bool isFileError();
private:
    std::unique_ptr<app> AP;
};

#endif // FAS_H
