#ifndef wioJsonSerializable
#define wioJsonSerializable

#include <iostream>


class JsonSerializable
{
    public:
        virtual std::string ToJson(double value, std::string measurementTime) {
            return "{\"value\": " 
                + std::to_string(value) 
                + ", \"dateTime\": \"" 
                + measurementTime 
                + "\"}";
        }
};


#endif // wioJsonSerializable

