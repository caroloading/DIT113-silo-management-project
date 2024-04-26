#ifndef wioJsonSerializable
#define wioJsonSerializable

#include <iostream>


class JsonSerializable
{
    public:
        virtual std::string ToJson(long value) {
            return "{\"value\": \"" + std::to_string(value) + "\"}";
        }
};


#endif // wioJsonSerializable

