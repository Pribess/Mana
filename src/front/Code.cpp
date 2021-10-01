// Copyright (c) 2021 Heewon Cho

#include "Code.hpp"

Code::Code(std::string filename, std::string code) {
    this->filename = filename;
    this->code = code;
}

void Code::TrimLiteral() {

    std::vector<std::string> buff;
    std::stringstream ss;

    static bool inLiteral = false;
    static int index = 0;

    for (std::string cnt : this->tokens) {

        if (cnt == " " && !inLiteral) {
            continue;
        } else if (cnt == "\n" && !inLiteral) {
            continue;
        }

        ss << cnt;

        if (cnt.front() == '"' && !inLiteral) {
            inLiteral = true;
        } else if (cnt.back() == '"' && inLiteral) {
            inLiteral = false;
        }
        
        if (cnt.back() == '"' && inLiteral) {
            inLiteral = false;
        }

        if (!inLiteral) {

            buff.push_back(ss.str());
            ss.str("");

        }

        index += cnt.size();

    }

    if (inLiteral) {
        std::cout << index << std::endl;
        ERROR::GERROR(this->filename, ERROR::GETROW(index, this->code), ERR_MISSING_DOUBLE_QUOTE_END);
        exit(1);
    }
    
    this->tokens = buff;

    for (auto cnt : buff) {
        std::cout << "(" << cnt << ")" << std::endl;
    }

}

void Code::Tokenize() {

    std::stringstream ss(this->code);
    std::string token;

    std::vector<std::string> buff;

    while (std::getline(ss, token, '\n')) {
        buff.push_back(token);
        buff.push_back("\n");
    }

    buff.erase(std::find(buff.begin(), buff.end(), std::string("")));

    for (std::string cnt : buff) {
        std::stringstream ss(cnt);
        while (std::getline(ss, token, ' ')) {
            this->tokens.push_back(token);
            this->tokens.push_back(" ");
        }
    }

    this->TrimLiteral();
}