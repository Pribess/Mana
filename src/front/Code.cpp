// Copyright (c) 2021 Heewon Cho

#include "Code.hpp"

Code::Code(std::string filename, std::string code) {
    this->filename = filename;
    this->code = code;
}

void Code::Tokenize() {

    std::stringstream ss(this->code);
    std::string token;

    while (std::getline(ss, token, '\n')) {
        this->lines.push_back(token);
    }

    

}