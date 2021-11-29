// Copyright (c) 2021 Heewon Cho

#ifndef CODE_HPP
#define CODE_HPP

#include <vector>
#include <string>
#include <sstream>
#include <iostream>

#include <front/lexer/Token.hpp>
#include <front/lexer/Lexer.hpp>
#include <utils/Error.hpp>

class Code {
    private:
        std::string filename;
        std::string code;

        Lexer *lexer;

    public:
        Code(std::string filename, std::string code);

};

#endif