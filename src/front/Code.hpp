// Copyright (c) 2021 Heewon Cho

#ifndef CODE_HPP
#define CODE_HPP

#include <vector>
#include <string>
#include <sstream>
#include <iostream>

#include "front/lexer/Token.hpp"
#include "utils/Error.hpp"

class Code {
    private:
        std::string filename;
        std::string code;

        std::vector<std::string> strtoken;
        std::vector<token> tokens;

    public:
        Code(std::string filename, std::string code);

        void Tokenize();
};

#endif