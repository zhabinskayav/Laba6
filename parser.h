#ifndef PARSER_H
#define PARSER_H

#include <string>
#include <jsonvalue.h>
#include <vector>
#include <jsontoken.h>
#include <error.h>

class parser
{
public:
    parser();
    std::tuple<JSONValue, err> parse(std::vector <JSONToken> &, int index = 0);
private:
    std::tuple < std::vector < JSONValue > , err > parseArray(std::vector < JSONToken > &tokens, int index);
    std::tuple < std::vector < std::pair < std::string, JSONValue >> , err> parseObjectSyntax(std::vector < JSONToken > & tokens, int index, bool comma, std::vector < std::pair < std::string, JSONValue >> & values);
    std::tuple < std::vector < std::pair < std::string, JSONValue >> , err > parseObject(std::vector < JSONToken > &tokens, int index);
    std::tuple<JSONValue, err> objectChecks(std::vector<JSONToken> &tokens, int& index);
};

#endif // PARSER_H
