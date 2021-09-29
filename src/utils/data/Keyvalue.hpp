// Copyright (c) 2021 Heewon Cho

#ifndef KEYVALUE_HPP
#define KEYVALUE_HPP

#include <unordered_map>
#include <string>

enum Key {
    mode,
    target
};

class Keyvalue {
    private:
        static std::unordered_map<Key, std::string> keyvalue;

    public:
        static void SetKey(Key key, std::string value);
        static std::string GetKey(Key key);
};

#endif