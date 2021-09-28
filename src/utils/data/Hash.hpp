// Copyright (c) 2021 Heewon Cho

#ifndef HASH_HPP
#define HASH_HPP

#include <ios>

namespace Utils {

    constexpr unsigned int Hashx65599(const char *str, size_t len) {
        unsigned int hash = 0;
        for(size_t i = 0; i < len; ++i) {
            hash = 65599 * hash + str[i];
        }
        return hash ^ (hash >> 16);
    }

};

#endif