#include "jsontoken.h"

JSONToken::JSONToken()
{

}

JSONToken::JSONToken(JSONTokenType type, int index):type(type),location(index)
{
}

std::shared_ptr<std::string> JSONToken::get_full_source()
{
    return fullSource;
}

void JSONToken::setFullSource(std::shared_ptr<std::string> source)
{
    fullSource = source;
}

void JSONToken::appendValue(char c)
{
    value+=c;
}

void JSONToken::setType(JSONTokenType type)
{
    JSONToken::type = type;
}

void JSONToken::setValue(std::string val)
{
    value = val;
}

std::string JSONToken::getValue()
{
    return value;
}

JSONTokenType JSONToken::getType()
{
    return type;
}

int JSONToken::getLocation()
{
    return location;
}
