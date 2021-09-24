// Copyright (c) 2021 Heewon Cho

#ifndef PREPROC_HPP
#define PREPROC_HPP

#include <vector>
#include <string>
#include <fstream>

class Preproc {
    private:
        std::string file;
    public:
        Preproc(std::string file);

        std::string run();
};

#endif