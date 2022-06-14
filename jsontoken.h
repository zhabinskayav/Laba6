#ifndef JSONTOKEN_H
#define JSONTOKEN_H
#include <string>

enum class JSONTokenType {
    String,
    Int,
    Double,
    Syntax,
    Boolean,
    Null
};

class JSONToken
{
public:
    JSONToken();
    JSONToken(JSONTokenType type, int index);
    std::shared_ptr<std::string>get_full_source();
    void setFullSource(std::shared_ptr<std::string> source);
    void appendValue(char c);
    void setType(JSONTokenType type);
    void setValue(std::string val);
    std::string getValue();
    JSONTokenType getType();
    int getLocation();
private:
    std::string value = "";
    JSONTokenType type;
    int location;
    std::shared_ptr<std::string> fullSource;
};

#endif // JSONTOKEN_H
