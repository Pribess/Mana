// Copyright (c) 2021 Heewon Cho

#ifndef DRIVER_HPP
#define DRIVER_HPP

#include <vector>
#include <string>
#include <sstream>
#include <fstream>

#include "front/Code.hpp"

class Driver {
    private:
        std::vector<std::string> filelist;
    public:
        Driver(std::vector<std::string> filelist);

        void run();
};

#endif