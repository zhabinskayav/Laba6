#include "logic.h"

app::app()
{

}

void app::readFile(const std::string &pathFileName)
{
    std::string data;
    char buf[pathFileName.length() + 1];
    strcpy(buf, pathFileName.c_str());
    FILE * fp = fopen(buf, "r");
    if(fp == NULL){
        error.setIndexAndBase(0, "Cannot open file");
    }
    char c = fgetc(fp);
    while (c != EOF) {
       data.push_back(c);
       c = fgetc(fp);
    }
    fclose(fp);
    file = data;
}

void app::parse(const std::string &source)
{
    lexer lex;
    lex.lex(source);
    auto tokens = lex.getTokens();
    app::error = lex.getError();
    if (error.getBase().size()) {
        app::error.setError(error.getBase(), error.getIndex());
        app::error.setIndexAndBase(error.getIndex(), app::error.formatError());
        return;
    }
    parser pars;
    auto[ast, error1] = pars.parse(tokens);
    app::error = error1;
    if (error1.getBase().size()) {
        app::error.setIndexAndBase(error.getIndex(), app::error.formatParseError());
        return;
    }
    jsonStr = deparser::deparse(ast);
}

void app::entryPoint(FuncType ft, const std::string &fa)
{
    try {
        switch(ft)
        {
            case FuncType::parse:
                parse(fa);
                break;
            case FuncType::readFile:
                readFile(fa);
                break;
            default:
                error.setError("Wrong case", 0);
            break;
        }
    }  catch (std::bad_alloc()) {
        error.setError("Memory fail", 0);
    }
}

void app::entryPoint(FuncType ft, JSONValue fa)
{
    try {
        switch(ft)
        {
            case FuncType::deparse:
                jsonStr = deparser::deparse(fa);
                break;
            default:
                error.setError("Wrong case", 0);
            break;
        }
    }  catch (std::bad_alloc()) {
        error.setError("Memory fail", 0);
    }
}

std::string app::getFile()
{
    return file;
}

std::string app::getError()
{
    return error.getBase();
}

std::string app::getJsonStr()
{
    return jsonStr;
}
