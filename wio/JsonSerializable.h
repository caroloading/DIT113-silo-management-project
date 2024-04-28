#ifndef wioJsonSerializable
#define wioJsonSerializable

#include <iostream>


class JsonSerializable
{
    public:
        virtual std::string ToJson(long value, std::string measurementTime) {
            return "{\"value\": " 
                + std::to_string(value) 
                + ", \"dateTime\": \"" 
                + measurementTime 
                + "\"}";
        }
};


#endif // wioJsonSerializable

