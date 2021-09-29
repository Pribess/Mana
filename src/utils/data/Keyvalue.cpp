// Copyright (c) 2021 Heewon Cho

#include "Keyvalue.hpp"

std::unordered_map<Key, std::string> Keyvalue::keyvalue;

void Keyvalue::SetKey(Key key, std::string value) {
    Keyvalue::keyvalue[key] = value;
}

std::string Keyvalue::GetKey(Key key) {
    return Keyvalue::keyvalue[key];
}