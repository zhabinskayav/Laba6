#ifndef LEXER_H
#define LEXER_H


#include <memory>
#include <string>
#include <vector>
#include <error.h>
#include <regex>
#include <jsontoken.h>


class lexer {
    public:
        lexer();
        void lex(std::string);
        err getError();
        std::vector < JSONToken > getTokens();
    private:
        std::tuple < std::vector < JSONToken > , err > tokens;
};

#endif // LEXER_H
