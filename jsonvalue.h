#ifndef JSONVALUE_H
#define JSONVALUE_H

#include <string>
#include <vector>
#include <jsontoken.h>

enum class JSONValueType {
    String,
    Int,
    Double,
    Object,
    Array,
    Boolean,
    Null
};

class JSONValue
{
public:
    JSONValue();
    JSONValue(JSONToken token, JSONValueType type);
    JSONValue(std::vector < JSONValue > array, JSONValueType type);
    JSONValue(std::vector < std::pair < std::string, JSONValue >> object, JSONValueType type);
    std::string getValue();
    std::vector <JSONValue> getArray();
    std::vector < std::pair < std::string, JSONValue >> getObject();
    JSONValueType getType();
    ~JSONValue();
private:
    std::shared_ptr<JSONToken> token;
    std::vector <JSONValue> array;
    std::vector < std::pair < std::string, JSONValue >> object;
    JSONValueType type;
};

#endif // JSONVALUE_H
