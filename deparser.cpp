#include "deparser.h"

deparser::deparser()
{

}

std::string deparse_array(JSONValue v, std::string whitespace){
    std::string s = "[\n";
    auto a = v.getArray();
    for (int i = 0; i < a.size(); i++) {
        auto value = a[i];
        s += whitespace + "  " + deparser::deparse(value, whitespace + "  ");
        if (i < a.size() - 1) {
            s += ",";
        }

        s += "\n";
    }
    return s + whitespace + "]";
}

std::string deparse_object(JSONValue v, std::string whitespace){
    std::string s = "{\n";
    auto values = v.getObject();
    auto i = 0;
    for (auto
        const & [key, value]: values) {
        s += whitespace + "  " + "\"" + key + "\": " + deparser::deparse(value, whitespace + "  ");

        if (i < values.size() - 1) {
            s += ",";
        }

        s += "\n";
        i++;
    }

    return s + whitespace + "}";
}

std::string deparser::deparse(JSONValue v, std::string whitespace)
{
    switch (v.getType()) {
    case JSONValueType::String:
        return "\"" + v.getValue() + "\"";
    case JSONValueType::Boolean:
        return (v.getValue());
    case JSONValueType::Int:
        return v.getValue();
    case JSONValueType::Double:
        return v.getValue();
    case JSONValueType::Null:
        return "null";
    case JSONValueType::Array: {
        return deparse_array(v, whitespace);
    }
    case JSONValueType::Object: {
        return deparse_object(v, whitespace);
    }
    }
}
