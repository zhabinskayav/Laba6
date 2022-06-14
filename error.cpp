#include "error.h"


err::err()
{

}

err::err(int index, const std::string & error):index(index),base(error)
{

}

err::err(int index,const std::string & error, std::shared_ptr<std::string> source):index(index),base(error),source(source)
{

}

err::err(int index, const std::string &error, JSONToken token):index(index)
{
    setParseError(error, token);
}

std::string err::formatParseError()
{
    std::ostringstream s;
    s << "Unexpected token '" << tokenValue << "', type '" <<
        tokenType << "'";
    s << std::endl << base;
    base = s.str();
    return formatError();
}

std::string err::JSONTokenTypeToString(JSONTokenType jtt)
{
    switch (jtt) {
    case JSONTokenType::String:
        return "String";
    case JSONTokenType::Int:
        return "Int";
    case JSONTokenType::Double:
        return "Double";
    case JSONTokenType::Syntax:
        return "Syntax";
    case JSONTokenType::Boolean:
        return "Boolean";
    case JSONTokenType::Null:
        return "Null";
    }
}

std::string err::formatError()
{
    std::ostringstream s;
    s << base << " at line " << line << ", column " << column << std::endl;
    s << lastline << std::endl;
    s << whitespace << "^";
    return s.str();
}

std::string err::getBase()
{
    return base;
}

int err::getIndex()
{
    return index;
}

void err::setIndexAndBase(int index, const std::string & error)
{
    err::index = index;
    err::base = error;
}

void err::setError(const std::string & base, int index)
{
    int counter = 0;
    err::column = 0;
    err::line  = 1;
    bool rFlag = false;
    for(auto it = source->begin(); it != source->end(); it++){
        char c = *it;
        if (counter == index) {
            break;
        }
        appendToLineAndSpace(c, rFlag);
        counter++;
    }


    auto c = source->at(counter);
    while (counter < source->size() && !(c == '\n' || c == '\r')) {
        lastline += c;
        counter++;
        c = source->at(counter);
    }
    err::base = base;
    err::index = index;
}

void err::setParseError(const std::string &base, JSONToken token)
{
    err::tokenValue = token.getValue();
    err::tokenType = JSONTokenTypeToString(token.getType());
    err::source = token.get_full_source();
    setError(base, token.getLocation());
}

void err::appendToLineAndSpace(char c, bool &rFlag)
{
    if (c == '\n') {
        if(!rFlag){
            line++;
            column = 0;
            lastline = "";
            whitespace = "";
        }
    } else if (c == '\r') {
        rFlag = true;
        line++;
        column = 0;
        lastline = "";
        whitespace = "";
    } else if (c == '\t') {
        column++;
        lastline += "    ";
        whitespace += "    ";
        rFlag = false;
    } else {
        column++;
        lastline += c;
        whitespace += " ";
        rFlag = false;
    }
}
