// Copyright (c) 2021 Heewon Cho

#include <front/Code.hpp>

Code::Code(std::string filename, std::string code) {
    this->filename = filename;
    this->code = code;

    this->lexer = new Lexer(this->filename, this->code);
    this->lexer->lex();
}