// Copyright (c) 2021 Heewon Cho

#ifndef KEYVALUE_H
#define KEYVALUE_H

#include <unordered_map>
#include <string>

class Keyvalue {
    private:
        static std::unordered_map<std::string, std::string> keyvalue;

    public:
        static void SetKey(std::string key, std::string value);
        static std::string GetKey(std::string key);
};

#endif