// Copyright (c) 2021 Heewon Cho

#ifndef PARSER_HPP
#define PARSER_HPP

#include <vector>
#include <string>
#include <sstream>
#include <iostream>

#include <front/lexer/Token.hpp>
#include <front/parser/Ast.hpp>
#include <utils/Error.hpp>

class Parser {
    private:
        std::string filename;
        std::string code;

        std::vector<token> tokens;

    public:

        Parser(std::string filename, std::string code);
        ~Parser();

        std::vector<token> parse();

};

#endif