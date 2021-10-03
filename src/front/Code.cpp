// Copyright (c) 2021 Heewon Cho

#include "Code.hpp"

Code::Code(std::string filename, std::string code) {
    this->filename = filename;
    this->code = code;
}

void Code::Tokenize() {

    std::stringstream ss(this->code);
    std::string tok;

    while (std::getline(ss, tok, '\n')) {
        this->lines.push_back(tok);
    }

    std::vector<std::string>::iterator viter = this->lines.begin();

    while (viter != this->lines.end()) {

        std::string::iterator iter = (*viter).begin();

        while (iter != (*viter).end()) {

            if (*iter == ' ' || *iter == '\t' || *iter == '\t') {

                iter++;

            } else if (*iter >= '0' && *iter <= '9') {

                std::string rst;

                while (*iter >= '0' && *iter <= '9') {
                    
                    rst.push_back(*iter++);

                }

                this->tokens.push_back(token{Token::Number, rst});

            } else if (*iter == '\"') {

                std::string rst;

                iter++;

                while (*iter >= ' ' && *iter <= '~' && *iter != '\"') {
                    rst.push_back(*iter++);
                }
                
                if (*iter != '\"') {
                    ERROR::GERROR(this->filename, ERROR::TOPOS(viter - this->lines.begin(), iter - (*viter).begin()), ERRMSG_MISSING_DOUBLE_QUOTE_END);
                }

                this->tokens.push_back(token{Token::String, rst});

            }

            iter++;

        }
        
        viter++;

    }

}