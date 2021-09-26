// Copyright (c) 2021 Heewon Cho

#ifndef DRIVER_HPP
#define DRIVER_HPP

#include <vector>
#include <string>

class Driver {
    private:
    public:
        Driver(std::vector<std::string> filelist);

        void run();
};

#endif