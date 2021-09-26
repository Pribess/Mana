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
        std::string file;

        std::string import(std::string origin, std::string::iterator iter, std::string dir);
    public:
        Preproc(std::string file);

        std::string run();
};

#endif