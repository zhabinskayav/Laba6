#include "parser.h"

parser::parser()
{
}
std::tuple<JSONValue, err> parser::parse(std::vector<JSONToken> &tokens, int index){
    auto token = tokens[index];
    std::tuple<JSONValue, err> ans;
    switch (token.getType()){
        case JSONTokenType::Double:
            ans = { JSONValue(token, JSONValueType::Double), err(index + 1, "") };
        break;
        case JSONTokenType::Int:
            ans = { JSONValue(token, JSONValueType::Int), err(index + 1, "") };
        break;
        case JSONTokenType::Boolean:
            ans = { JSONValue(token, JSONValueType::Boolean), err(index + 1, "") };
        break;
        case JSONTokenType::Null:
            ans = { JSONValue(token, JSONValueType::Null), err(index + 1, "") };
        break;
        case JSONTokenType::String:
           ans = { JSONValue(token, JSONValueType::String), err(index + 1, "") };
        break;
        case JSONTokenType::Syntax:
            if (token.getValue() == "["){
                auto[array, error] = parseArray(tokens, index + 1);
                ans ={ JSONValue(array, JSONValueType::Array), error};
                break;
            }else if (token.getValue() == "{"){
                auto[object, error] = parseObject(tokens, index + 1);
                ans = { JSONValue(object, JSONValueType::Object), error};
                break;
            }
        default:
            ans = { {}, err(index, "Failed to parse", token) };
    }
    return ans;
}


std::tuple < std::vector < JSONValue > , err > parser::parseArray(std::vector<JSONToken> &tokens, int index){
    std::vector<JSONValue> children = {};
    bool comma = true;
    bool flag = true;
    std::tuple < std::vector < JSONValue > , err > ans;
    while (index < tokens.size()){
        auto t = tokens[index];
        if (t.getType() == JSONTokenType::Syntax){
            if (t.getValue() == "]"){
                flag = false;
                ans = { children, err(index + 1, "") };
                break;
            }
            if (t.getValue() == "," ){
                index++;
                t = tokens[index];
                comma = true;
            }
        }
        if (!comma && flag){
            flag = false;
            ans = { {},  err(index, "Expected comma before element in array", t)};
            break;
        }
        auto[child, error] = parse(tokens, index);
        if (error.getBase().size() && flag){
            flag = false;
            ans =  { {}, error};
            break;
        }
        if (flag){
            children.push_back(child);
            index = error.getIndex();
            comma = false;
        }
    }
    if(flag)
        ans = { {}, err(index, "Unexpected EOF while parsing array",tokens[index])};
    return ans;
}

std::tuple<std::vector<std::pair<std::string, JSONValue>>, err>
parser::parseObjectSyntax(std::vector<JSONToken>& tokens, int index, bool comma,std::vector<std::pair<std::string, JSONValue>>& values)
{
    auto t = tokens[index];
    bool flag = true;
    std::tuple<std::vector<std::pair<std::string, JSONValue>>, err> ans;
    if (t.getType() == JSONTokenType::Syntax)
    {
        if (t.getValue() == "}"){
            flag = false;
            ans = { values, err(index + 1, "")};
        }
        if (t.getValue() == "," && flag){
            comma = true;
            index++;
        }
        else if (!(values.size() > 0) && flag)
        {
            flag = false;
            ans = { {}, err(index, "Expected key-value pair or closing brace in object", t)};
        }
    }
    if (!comma && flag){
        flag = false;
        ans = { {}, err(index, "Expected comma before element in object", t)};
    }
    if(flag)
        ans = { {}, err(index, "NoError")};
    return ans;
}

std::tuple<std::vector<std::pair<std::string, JSONValue>>, err> parser::parseObject(std::vector<JSONToken> &tokens, int index){
    std::vector<std::pair<std::string, JSONValue>> values = {};
    bool comma = true;
    bool flag = true;
    std::tuple<std::vector<std::pair<std::string, JSONValue>>, err> ans;
    while (index < tokens.size() && flag)
    {
        auto res = parseObjectSyntax(tokens, index, comma, values);
        if (std::get<1>(res).getBase() != "NoError"){
            ans = res;
            flag = false;
            break;
        }
        index = std::get<1>(res).getIndex();
        auto[key, error] = parse(tokens, index);
        if (error.getBase().size()){
            ans = { {}, err(index, error.getBase()) };
            flag = false;
            break;
        }
        if (key.getType() != JSONValueType::String){
            ans = { {}, err(index, "Expected string key in object", tokens[index]) };
            flag = false;
            break;
        }
        index = error.getIndex();
        auto[value, error1] = objectChecks(tokens, index);
        if (error1.getBase().size()){
            ans = { {}, err(index, error1.getBase()) };
            flag = false;
            break;
        }
        values.push_back(std::make_pair(key.getValue(), value));
        index = error1.getIndex();
        comma = false;
    }
    if (flag)
        ans = { values, err(index + 1, "" )};
    return ans;
}

std::tuple<JSONValue, err> parser::objectChecks(std::vector<JSONToken> &tokens, int &index)
{
    if (!(tokens[index].getType() == JSONTokenType::Syntax && tokens[index].getValue() == ":")){
        return { {}, err(index, "Expected colon after key in object", tokens[index])};
    }
    index++;

    return parse(tokens, index);
}
