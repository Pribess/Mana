// Copyright (c) 2021 Heewon Cho

#ifndef HASH_HPP
#define HASH_HPP

namespace Utils {

    constexpr unsigned int Hashx65599(const char *str) {
        unsigned int hash = 0;
        while (*str) {
            hash = 65599 * hash + str[0];
            str++;
        }
        return hash ^ (hash >> 16);
    }

};

#endif