// Copyright (c) 2021 Heewon Cho

#ifndef PREPROC_HPP
#define PREPROC_HPP

#include <vector>
#include <string>
#include <fstream>
#include <sstream>

#include "utils/data/Hash.hpp"
#include "utils/Error.hpp"

class Preproc {
    private:
        static std::vector<std::string> filelist;

        std::string filename;
        std::string file;

        void import(std::string::iterator begin, std::string::iterator end, std::string dir);
    public:
        Preproc(std::string filename);
        Preproc(std::string filename, std::string filenameprev, std::string pos);

        std::string run();
};

#endif