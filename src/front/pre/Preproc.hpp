// Copyright (c) 2021 Heewon Cho

#ifndef PREPROC_HPP
#define PREPROC_HPP

#include <fstream>
#include <string>
#include <unordered_map>

class Preproc {
    private:
        std::unordered_map<std::string, std::string> deflist;
    public:
        Preproc(std::unordered_map<std::string, std::string> predef);
        ~Preproc();
};

#endif