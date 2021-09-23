// Copyright (c) 2021 Heewon Cho

#ifndef PREPROC_HPP
#define PREPROC_HPP

#include <string>
#include <unordered_map>

class Preproc {
    private:
        std::unordered_map<std::string, std::string> deflist;
    public:
        Preproc();
        ~Preproc();
};

#endif