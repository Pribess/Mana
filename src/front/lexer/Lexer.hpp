// Copyright (c) 2021 Heewon Cho

#ifndef LEXER_HPP
#define LEXER_HPP

#include <vector>
#include <string>
#include <sstream>
#include <iostream>

#include <front/lexer/Token.hpp>
#include <utils/Error.hpp>

class Lexer {
    private:
        std::string filename;
        std::string code;

        std::vector<token> tokens;
        
    public:
        Lexer(std::string filename, std::string code);
        ~Lexer();

        std::vector<token> lex();

};

#endif