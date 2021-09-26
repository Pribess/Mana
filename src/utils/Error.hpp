// Copyright (c) 2021 Heewon Cho

#ifndef ERROR_HPP
#define ERROR_HPP

#include "Color.hpp"

#include <string>
#include <iostream>

std::string GETPOS(std::string::iterator iter, std::string src);

#define GERROR(at, str) std::cout << at << RED << "fatal error:" << RESET << str << std::endl;

#endif