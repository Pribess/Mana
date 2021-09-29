// Copyright (c) 2021 Heewon Cho

#include "Code.hpp"

Code::Code(std::string filename, std::string code) {
    this->filename = filename;
    this->code = code;
}

void Code::TrimLiteral() {

    
}

void Code::Tokenize() {

    std::stringstream ss(this->code);
    std::string token;

    while (std::getline(ss, token, ' ')) {
        this->tokens.push_back(token);
    }

    for (auto cnt : this->tokens) {
        std::cout << cnt << std::endl;
    }
}