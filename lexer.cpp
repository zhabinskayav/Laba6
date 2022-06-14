#include "lexer.h"

lexer::lexer() {

}



int lex_whitespace(std::shared_ptr<std::string> raw_json, int index) {
    while ((index < raw_json->length()) && std::isspace(raw_json->at(index))) {
        index++;
    }

    return index;
}

std::tuple < JSONToken, int, err > lex_syntax(std::shared_ptr<std::string> raw_json, int index) { //синтаксические части
    JSONToken token(JSONTokenType::Syntax, index);
    std::string value = "";
    std::tuple < JSONToken, int, err > ans;
    auto c = raw_json->at(index);
    if (c == '[' || c == ']' || c == '{' || c == '}' || c == ':' || c == ',') {
        token.appendValue(c);
        index++;
        ans = {token, index, err(index, "")};
    } else {
        ans = {token, index, err(index, "Invalid syntax", raw_json)};
    }

    return ans;
}


std::tuple < JSONToken, int, err > lex_string(std::shared_ptr<std::string> raw_json, int original_index) {
    int index = original_index;
    bool flag = true;
    JSONToken token (JSONTokenType::String, index);
    std::string value = "";
    std::tuple < JSONToken, int, err > ans;
    char c = raw_json->at(index);
    if (c != '"') {
        flag = false;
        ans = {token, original_index, err(index, "No \" in sting", raw_json)};
    } else {
        index++;
        while ((raw_json->at(index) != '"') || (raw_json->at(index+1) == '"' && raw_json->at(index) == '\\')) {
            if (index == raw_json->length()) {
                flag = false;
                ans = {token, index, err(index, "Unexpected EOF while lexing string", raw_json)};
                break;
            }
            if(raw_json->at(index) == '\\'){
                index++;
            }
            token.appendValue(raw_json->at(index));
            index++;
        }
        if (flag)
         index++;
    }
    if (flag)
        ans = {token, index, err(index, "")};
    return ans;
}

std::tuple < JSONToken, int, err > lex_number(std::shared_ptr<std::string> raw_json, int original_index) {
    int index = original_index;
    JSONToken token (JSONTokenType::Int, index);
    char c = raw_json->at(index);
    bool flag = true;
    std::tuple < JSONToken, int, err > ans;
    while (index < raw_json->length() && ((c >= '0' && c <= '9') || c == '.' || c == '-')) {
        token.appendValue(c);
        index++;
        c = raw_json->at(index);
    }
    if((token.getValue().find_last_of("-") != 0) && (token.getValue().find_first_of("-") != std::string::npos)){
         ans = {token, original_index, err(index, "Incorrect - pos", raw_json)};
         flag = false;
    }
    if((token.getValue().find_first_of(".") != std::string::npos) && flag){
        if (token.getValue().find_first_of(".") != token.getValue().find_last_of(".")){
            ans = {token, original_index, err(index, "Exessive \".\"", raw_json)};
            flag = false;
        }
        token.setType(JSONTokenType::Double);
    } else if ((token.getValue()[0] == '0' && token.getValue().length() != 1) && flag){
        ans =  {token, original_index, err(index, "Incorrect number", raw_json)};
        flag = false;
    }
    if (original_index == index && flag) {
        ans = {token, original_index, err(index, "Not a number char", raw_json)};
        flag = false;
    }
    if(flag){
        ans = {token, index, err(index, "")};
    }
    return ans;
}

std::tuple < JSONToken, int, err > lex_keyword(std::shared_ptr<std::string> raw_json, std::string keyword, JSONTokenType type, int original_index) {
    int index = original_index;
    JSONToken token (type, index);
    std::string sub = raw_json->substr(index, keyword.length());

    if (sub == keyword) {
        token.setValue(keyword);
        index += keyword.length();
    } else {
        return {token, original_index, err(index, "Not a keyword", raw_json)};
    }

    return {token, index, err(index, "")};
}

std::tuple < JSONToken, int, err > lex_null(std::shared_ptr<std::string> raw_json, int index) {
    return lex_keyword(raw_json, "null", JSONTokenType::Null, index);
}

std::tuple < JSONToken, int, err > lex_true(std::shared_ptr<std::string> raw_json, int index) {
    return lex_keyword(raw_json, "true", JSONTokenType::Boolean, index);
}

std::tuple < JSONToken, int, err > lex_false(std::shared_ptr<std::string> raw_json, int index) {
    return lex_keyword(raw_json, "false", JSONTokenType::Boolean, index);
}

void lexer::lex(std::string raw_json){
    int newIndex;
    bool found;
    std::vector < JSONToken > tokens;
    auto original_copy = std::make_shared<std::string>(raw_json);
    auto generic_lexers = {lex_syntax, lex_string, lex_number, lex_null, lex_true, lex_false};
    for (int i = 0; i < raw_json.length(); i++) {
        newIndex = lex_whitespace(original_copy, i);
        if (i == newIndex) {
            found = false;
            for (auto lexer: generic_lexers) {
                if (auto[token, newIndex, error] = lexer(original_copy, i); i != newIndex) {
                    if (error.getBase().length()) {
                         lexer::tokens = {{},error};
                         break;
                    }
                    token.setFullSource(original_copy);
                    tokens.push_back(token);
                    i = newIndex - 1;
                    found = true;
                    break;
                }
            }
            if (!found) {
                lexer::tokens = {{}, err(i, "Unable to lex", original_copy)};
                break;
            }

        } else {
            i = newIndex - 1;
        }
        if(std::get<1>(lexer::tokens).getBase() != ""){
            break;
        }
    }
    lexer::tokens = {tokens, err(0, "")};
}

err lexer::getError()
{
    return std::get<1>(tokens);
}

std::vector<JSONToken> lexer::getTokens()
{
    return std::get<0>(tokens);
}
