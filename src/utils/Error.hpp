// Copyright (c) 2021 Heewon Cho

#ifndef ERROR_HPP
#define ERROR_HPP

#include "Color.hpp"

#include <string>
#include <iostream>

namespace Error {

    std::string GETPOS(std::string::iterator iter, std::string *src);

}

#define ERROR(str) std::cout << str << std::endl;
#define GERROR(filename, at, str) std::cout << filename << ": " << at << RED << "fatal error:" << RESET << str << std::endl;

#endif