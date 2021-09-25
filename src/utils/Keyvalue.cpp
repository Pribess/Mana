// Copyright (c) 2021 Heewon Cho

#include "Keyvalue.hpp"

std::unordered_map<std::string, std::string> Keyvalue::keyvalue;

void Keyvalue::SetKey(std::string key, std::string value) {
    Keyvalue::keyvalue[key] = value;
}

std::string Keyvalue::GetKey(std::string key) {
    return Keyvalue::keyvalue[key];
}