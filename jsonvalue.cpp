#include "jsonvalue.h"

JSONValue::JSONValue()
{

}

JSONValue::JSONValue(JSONToken token, JSONValueType type)
{
    JSONValue::token = std::make_shared<JSONToken>(token);
    JSONValue::type = type;
}

JSONValue::JSONValue(std::vector<JSONValue> array, JSONValueType type):array(array),type(type)
{
}

JSONValue::JSONValue(std::vector<std::pair<std::string, JSONValue> > object, JSONValueType type):object(object),type(type)
{
}

std::string JSONValue::getValue()
{

    return  token->getValue();
}

std::vector<JSONValue> JSONValue::getArray()
{
    return array;
}

std::vector<std::pair<std::string, JSONValue> > JSONValue::getObject()
{
    return object;
}

JSONValueType JSONValue::getType()
{
    return  type;
}

JSONValue::~JSONValue()
{
    token.reset();
}
