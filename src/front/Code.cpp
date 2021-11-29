// Copyright (c) 2021 Heewon Cho

#include <front/Code.hpp>

Code::Code(std::string filename, std::string code) {
    this->filename = filename;
    this->code = code;
}

token lexnum(int line, std::vector<std::string>::iterator &liter, std::string::iterator &iter, std::string filename) {

    token tok;
    tok.tok = Token::Number;
    int ebegin = iter - liter[0].begin();

    if (iter[0] == '0' && iter[1] == 'x') {
        // hex
        
        tok.str.push_back(iter[0]);
        iter++;
        tok.str.push_back(iter[0]);
        iter++;

        while ((iter[0] >= '0' && iter[0] <= '9') || (iter[0] >= 'A' && iter[0] <= 'F') || (iter[0] >= 'a' && iter[0] <= 'f')) {

        tok.str.push_back(iter[0]);
        iter++;

        }

        if (!(iter[0] == ' ' || iter == liter[0].end())) {

            int eend = iter - liter[0].begin() + 1;
            ERROR::GERROR(GERRMSG_INVALID_CONSTANT_FORMAT, filename, line, liter, iter, ebegin, eend);

        }

    } else if (iter[0] == '0' && iter[1] == 'd') {
        // dec

        tok.str.push_back(iter[0]);
        iter++;
        tok.str.push_back(iter[0]);
        iter++;

        while (iter[0] >= '0' && iter[0] <= '9') {

            tok.str.push_back(iter[0]);
            iter++;

        }

    } else if (iter[0] == '0' && iter[1] == 'o') {
        // oct
                    
        tok.str.push_back(iter[0]);
        iter++;
        tok.str.push_back(iter[0]);
        iter++;

        while (iter[0] >= '0' && iter[0] <= '9') {

            if (iter[0] >= '8' && iter[0] <= '9') {

                int eend = iter - liter[0].begin() + 1;
                ERROR::GERROR(GERRMSG_INVALID_CONSTANT_FORMAT, filename, line, liter, iter, ebegin, eend);

            }

            tok.str.push_back(iter[0]);
            iter++;

        }

        if (!(iter[0] == ' ' || iter == liter[0].end())) {

            int eend = iter - liter[0].begin() + 1;
            ERROR::GERROR(GERRMSG_INVALID_CONSTANT_FORMAT, filename, line, liter, iter, ebegin, eend);

        }

    } else if (iter[0] == '0' && iter[1] == 'b') {
        // bin

        tok.str.push_back(iter[0]);
        iter++;
        tok.str.push_back(iter[0]);
        iter++;

        while (iter[0] >= '0' && iter[0] <= '9') {

            if (iter[0] >= '2' && iter[0] <= '9') {

                int eend = iter - liter[0].begin() + 1;
                ERROR::GERROR(GERRMSG_INVALID_CONSTANT_FORMAT, filename, line, liter, iter, ebegin, eend);

            }

            tok.str.push_back(iter[0]);
            iter++;

        }

        if (!(iter[0] == ' ' || iter == liter[0].end())) {

            int eend = iter - liter[0].begin() + 1;
            ERROR::GERROR(GERRMSG_INVALID_CONSTANT_FORMAT, filename, line, liter, iter, ebegin, eend);

        }

    } else {
        // dec (default)

        while (iter[0] >= '0' && iter[0] <= '9') {

            tok.str.push_back(iter[0]);
            iter++;

        }

        if (!(iter[0] == ' ' || iter == liter[0].end())) {

            int eend = iter - liter[0].begin() + 1;
            ERROR::GERROR(GERRMSG_INVALID_CONSTANT_FORMAT, filename, line, liter, iter, ebegin, eend);

        }

    }

    return tok;

}

token lexstr(int line, std::vector<std::string>::iterator &liter, std::string::iterator &iter, std::string filename) {

    token tok;
    tok.tok = Token::String;
    int ebegin = iter - liter[0].begin();
                
    tok.str.push_back(iter[0]);
    iter++;

    while (iter[0] >= ' ' && iter[0] <= '~' && iter[0] != '\"') {
        tok.str.push_back(iter[0]);
        iter++;
    }

    if (iter[0] != '\"') {

        int eend = iter - liter[0].begin() + 1;
        ERROR::GERROR(GERRMSG_MISSING_DOUBLE_QUOTE_END, filename, line, liter, iter, ebegin, eend);

    }

    tok.str.push_back(iter[0]);
    iter++;

    return tok;

}

token lexchar(int line, std::vector<std::string>::iterator &liter, std::string::iterator &iter, std::string filename) {

    token tok;
    tok.tok = Token::Char;
    int ebegin = iter - liter[0].begin();

    tok.str.push_back(iter[0]);
    iter++;

    while (iter[0] >= ' ' && iter[0] <= '~' && iter[0] != '\'') {
        tok.str.push_back(iter[0]);
        iter++;
    }

    if (iter[0] != '\'') {

        int eend = iter - liter[0].begin() + 1;
        ERROR::GERROR(GERRMSG_MISSING_SINGLE_QUOTE_END, filename, line, liter, iter, ebegin, eend);

    }

    tok.str.push_back(iter[0]);
    iter++;

    return tok;

}

token lexidentifierandkeyword(int line, std::vector<std::string>::iterator &liter, std::string::iterator &iter, std::string filename) {

    token tok;
    int ebegin = iter - liter[0].begin();
    
    while ((iter[0] >= 'A' && iter[0] <= 'Z') || (iter[0] >= 'a' && iter[0] <= 'z') || (iter[0] >= '0' && iter[0] <= '9')) {

        tok.str.push_back(iter[0]);
        iter++;

    }

    if (tokenmap[tok.str] == Token::Double || tokenmap[tok.str] == Token::Float) {
        // lex keyword

        tok.tok = tokenmap[tok.str];

        if (iter[0] != '(') {

            int eend = iter - liter[0].begin() + 1;
            ERROR::GERROR(GERRMSG_KEYWORD_MISSING_LPAREN, filename, line, liter, iter, ebegin, eend);

        }
        
        tok.str.push_back(iter[0]);
        iter++;

        if (iter[0] == ')') {

            int eend = iter - liter[0].begin() + 1;
            ERROR::GERROR(GERRMSG_MISSING_ARG_KEYWORD, filename, line, liter, iter, ebegin, eend);

        }

        std::string arg;

        if (!((iter[0] >= 'A' && iter[0] <= 'Z') || (iter[0] >= 'a' && iter[0] <= 'z'))) {

            int eend = iter - liter[0].begin() + 1;
            ERROR::GERROR(GERRMSG_INVALID_IDENTIFIER_FORMAT, filename, line, liter, iter, ebegin, eend);

        }

        while (iter[0] != ')') {
            if (!((iter[0] >= 'A' && iter[0] <= 'Z') || (iter[0] >= 'a' && iter[0] <= 'z') || (iter[0] >= '0' && iter[0] <= '9'))) {

                int eend = iter - liter[0].begin() + 1;
                ERROR::GERROR(GERRMSG_INVALID_IDENTIFIER_FORMAT, filename, line, liter, iter, ebegin, eend);

            }
            arg.push_back(iter[0]);
            iter++;
        }

        tok.str.append(arg);

        tok.str.push_back(iter[0]);
        iter++;

        return tok;

    }

    if (!(iter[0] == ' ' || iter == liter[0].end())) {

        int eend = iter - liter[0].begin() + 1;
        ERROR::GERROR(GERRMSG_INVALID_IDENTIFIER_FORMAT, filename, line, liter, iter, ebegin, eend);

    }

    if (tokenmap[tok.str]) {
        tok.tok = tokenmap[tok.str];
        return tok;
    } else {
        tok.tok = Token::Identifier;
        return tok;
    }

}

token lexoperator(int line, std::vector<std::string>::iterator &liter, std::string::iterator &iter, std::string filename) {

    token tok;
    int ebegin = iter - liter[0].begin();

    if (iter[0] == '<' && ((iter[1] >= 'A' && iter[1] <= 'Z') || (iter[1] >= 'a' && iter[1] <= 'z'))) {
        // lex pop

        tok.str.push_back('<');
        iter++;

        while ((iter[0] >= 'A' && iter[0] <= 'Z') || (iter[0] >= 'a' && iter[0] <= 'z') || (iter[0] >= '0' && iter[0] <= '9')) {

            tok.str.push_back(iter[0]);
            iter++;

        }

        if (iter[0] != '>') {
            int eend = iter - liter[0].begin() + 1;

            ERROR::GERROR(GERRMSG_MISSING_GREATERTHENSIGN, filename, line, liter, iter, ebegin, eend);
            
        }

        tok.tok = Token::Pop;
        return tok;

    } else {

    }

}

void Code::Tokenize() {

    std::stringstream ss(this->code);
    std::vector<std::string> lines;

    std::string line;
    while (std::getline(ss, line, '\n')) {
        lines.push_back(line);
    }

    std::vector<std::string>::iterator liter = lines.begin();

    while (liter != lines.end()) {
        
        std::string::iterator iter = liter[0].begin();

        while (iter != liter[0].end()) {

            token tok;
            tok.tok = Token::Unknown;

            if (iter[0] == ' ' || iter[0] == '\t' || iter[0] == '\r') {

                iter++;

            } else if (iter[0] >= '0' && iter[0] <= '9') {
                
                this->tokens.push_back(lexnum(liter - lines.begin() + 1 , liter, iter, this->filename));

            } else if (iter[0] == '\"') {

                this->tokens.push_back(lexstr(liter - lines.begin() + 1 , liter, iter, this->filename));

            } else if (iter[0] == '\'') {
                
                this->tokens.push_back(lexchar(liter - lines.begin() + 1 , liter, iter, this->filename));

            } else if ((iter[0] >= 'A' && iter[0] <= 'Z') || (iter[0] >= 'a' && iter[0] <= 'z')) {

                this->tokens.push_back(lexidentifierandkeyword(liter - lines.begin() + 1 , liter, iter, this->filename));

            } else if ((iter[0] >= '!' && iter[0] <= '/') || (iter[0] >= ':' && iter[0] <= '@') || (iter[0] >= '[' && iter[0] <= '`') || (iter[0] >= '{' && iter[0] <= '~')
                && iter[0] != '"' && iter[0] != '\'') {

                this->tokens.push_back(lexoperator(liter - lines.begin() + 1 , liter, iter, this->filename));

            }

        }

        liter++;

    }

    for (auto cnt : this->tokens) {
        std::cout << cnt.str << ":" << cnt.tok << std::endl;
    }

}