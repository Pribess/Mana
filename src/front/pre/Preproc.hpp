// Copyright (c) 2021 Heewon Cho

#ifndef PREPROC_HPP
#define PREPROC_HPP

#include <vector>
#include <string>
#include <fstream>
#include <sstream>

#include "utils/Hash.hpp"
#include "utils/Error.hpp"

class Preproc {
    private:
        std::string filename;
        std::string file;

        void import(std::string::iterator begin, std::string::iterator end, std::string dir);
    public:
        Preproc(std::string filename);

        std::string run();
};

#endif