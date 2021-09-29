// Copyright (c) 2021 Heewon Cho

#include "Driver.hpp"

Driver::Driver(std::vector<std::string> filelist) {
    this->filelist = filelist;
}

void Driver::run() {
    std::ifstream ifs(filelist.at(0));
    std::stringstream ss;
    ss<<ifs.rdbuf();
    Code c(filelist.at(0), ss.str());
    c.Tokenize();
}