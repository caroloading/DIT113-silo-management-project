#ifndef wioJsonSerializable
#define wioJsonSerializable

#include <iostream>


class JsonSerializable
{
    public:
        virtual std::string ToJson(const char* value)
        {
            return "{\"value\": " + (std::string)value + "}";
        }
};


#endif // wioJsonSerializable

