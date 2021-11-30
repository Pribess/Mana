// Copyright (c) 2021 Heewon Cho

#include <front/lexer/Lexer.hpp>

Lexer::Lexer(std::string filename, std::string code) {
    this->filename = filename;
    this->code = code;
}

token lexnum(int line, std::vector<std::string>::iterator &liter, std::string::iterator &iter, std::string filename) {

    int ebegin = iter - liter[0].begin() + 1;
    token tok;
    tok.line = line;
    tok.pos.first = ebegin;
    tok.tok = Token::Number;

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

    } else {
        // dec (default)

        bool prime = false;

        while ((iter[0] >= '0' && iter[0] <= '9') || iter[0] == '.') {

            tok.str.push_back(iter[0]);
            iter++;

            if (iter[0] == '.' && prime) {
                int eend = iter - liter[0].begin() + 1;
                ERROR::GERROR(GERRMSG_INVALID_CONSTANT_FORMAT, filename, line, liter, iter, ebegin, eend);
            }

            if (iter[0] == '.') {
                prime = true;
            }

        }

    }

    if (!(iter[0] == ' ' || iter == liter[0].end()) && !(iter[0] == '[' || iter[0] == ']' || iter[0] == '{' || iter[0] == '}' || iter[0] == '(' || iter[0] == ')' || iter[0] == ';')) {

            int eend = iter - liter[0].begin() + 1;
            ERROR::GERROR(GERRMSG_INVALID_CONSTANT_FORMAT, filename, line, liter, iter, ebegin, eend);

    }

    tok.pos.second = iter - liter[0].begin();
    return tok;

}

token lexstr(int line, std::vector<std::string>::iterator &liter, std::string::iterator &iter, std::string filename) {

    int ebegin = iter - liter[0].begin() + 1;

    token tok;
    tok.line = line;
    tok.pos.first = ebegin;
    tok.tok = Token::String;
    
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

    tok.pos.second = iter - liter[0].begin();
    return tok;

}

token lexchar(int line, std::vector<std::string>::iterator &liter, std::string::iterator &iter, std::string filename) {

    int ebegin = iter - liter[0].begin() + 1;

    token tok;
    tok.line = line;
    tok.pos.first = ebegin;
    tok.tok = Token::Char;

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

    tok.pos.second = iter - liter[0].begin();
    return tok;

}

token lexidentifierandkeyword(int line, std::vector<std::string>::iterator &liter, std::string::iterator &iter, std::string filename) {

    int ebegin = iter - liter[0].begin() + 1;

    token tok;
    tok.line = line;
    tok.pos.first = ebegin;
    
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
            if (iter == liter[0].end()) {

                int eend = iter - liter[0].begin() + 1;
                ERROR::GERROR(GERRMSG_KEYWORD_MISSING_RPAREN, filename, line, liter, iter, ebegin, eend);

            }
            if (!((iter[0] >= 'A' && iter[0] <= 'Z') || (iter[0] >= 'a' && iter[0] <= 'z') || (iter[0] >= '0' && iter[0] <= '9'))) {
                
                int eend = iter - liter[0].begin() + 1;
                if (iter[0] == ' ') {
                    ERROR::GERROR(GERRMSG_KEYWORD_MISSING_RPAREN, filename, line, liter, iter, ebegin, eend);
                } else {
                    ERROR::GERROR(GERRMSG_INVALID_IDENTIFIER_FORMAT, filename, line, liter, iter, ebegin, eend);
                }

            }

            arg.push_back(iter[0]);
            iter++;
        }

        tok.str.append(arg);

        tok.str.push_back(iter[0]);
        iter++;

        if (!(iter[0] == ' ' || iter == liter[0].end()) && !(iter[0] == '[' || iter[0] == ']' || iter[0] == '{' || iter[0] == '}' || iter[0] == '(' || iter[0] == ')' || iter[0] == ';')) {

            int eend = iter - liter[0].begin() + 1;
            ERROR::GERROR(GERRMSG_INVALID_KEYWORD_FORMAT, filename, line, liter, iter, ebegin, eend);

        }

        tok.pos.second = iter - liter[0].begin();
        return tok;

    }

    if (!(iter[0] == ' ' || iter == liter[0].end()) && !(iter[0] == '[' || iter[0] == ']' || iter[0] == '{' || iter[0] == '}' || iter[0] == '(' || iter[0] == ')' || iter[0] == ';' || iter[0] == ',')) {

        int eend = iter - liter[0].begin() + 1;
        ERROR::GERROR(GERRMSG_INVALID_IDENTIFIER_FORMAT, filename, line, liter, iter, ebegin, eend);

    }

    if (tokenmap[tok.str]) {
        tok.tok = tokenmap[tok.str];
        tok.pos.second = iter - liter[0].begin();
        return tok;
    } else {
        tok.tok = Token::Identifier;
        tok.pos.second = iter - liter[0].begin();
        return tok;
    }

}

token lexoperator(int line, std::vector<std::string>::iterator &liter, std::string::iterator &iter, std::string filename) {

    int ebegin = iter - liter[0].begin() + 1;

    token tok;
    tok.line = line;
    tok.pos.first = ebegin;

    if (iter[0] == '<' && ((iter[1] >= 'A' && iter[1] <= 'Z') || (iter[1] >= 'a' && iter[1] <= 'z'))) {
        // lex pop

        tok.str.push_back(iter[0]);
        iter++;

        while ((iter[0] >= 'A' && iter[0] <= 'Z') || (iter[0] >= 'a' && iter[0] <= 'z') || (iter[0] >= '0' && iter[0] <= '9')) {

            tok.str.push_back(iter[0]);
            iter++;

        }

        if (iter[0] != '>') {
            
            int eend = iter - liter[0].begin() + 1;
            ERROR::GERROR(GERRMSG_MISSING_GREATERTHENSIGN, filename, line, liter, iter, ebegin, eend);
            
        }

        tok.str.push_back(iter[0]);
        iter++;

        if (!(iter[0] == ' ' || iter == liter[0].end()) && !(iter[0] == '[' || iter[0] == ']' || iter[0] == '{' || iter[0] == '}' || iter[0] == '(' || iter[0] == ')' || iter[0] == ';')) {

            int eend = iter - liter[0].begin() + 1;
            ERROR::GERROR(GERRMSG_INVALID_KEYWORD_FORMAT, filename, line, liter, iter, ebegin, eend);

        }

        tok.tok = Token::Pop;
        tok.pos.second = iter - liter[0].begin();
        return tok;

    } else if (iter[0] == '-' && (iter[1] >= '0' && iter[1] <= '9')) {
        // lex negative

        tok.str.push_back(iter[0]);
        iter++;

        bool prime = false;

        while ((iter[0] >= '0' && iter[0] <= '9') || iter[0] == '.') {
            
            tok.str.push_back(iter[0]);
            iter++;

            if (iter[0] == '.' && prime) {
                int eend = iter - liter[0].begin() + 1;
                ERROR::GERROR(GERRMSG_INVALID_CONSTANT_FORMAT, filename, line, liter, iter, ebegin, eend);
            }

            if (iter[0] == '.') {
                prime = true;
            }

        }

        tok.tok = Token::Number;
        tok.pos.second = iter - liter[0].begin();
        return tok;

    } else if ((iter[0] == '*' || iter[0] == '&') && ((iter[1] >= 'A' && iter[1] <= 'Z') || (iter[1] >= 'a' && iter[1] <= 'z'))) {
        // lex pointer

        tok.str.push_back(iter[0]);
        iter++;

        tok.tok = tokenmap[tok.str];

        while ((iter[0] >= 'A' && iter[0] <= 'Z') || (iter[0] >= 'a' && iter[0] <= 'z') || (iter[0] >= '0' && iter[0] <= '9')) {

            tok.str.push_back(iter[0]);
            iter++;

        }

        if (!(iter[0] == ' ' || iter == liter[0].end()) && !(iter[0] == '[' || iter[0] == ']' || iter[0] == '{' || iter[0] == '}' || iter[0] == '(' || iter[0] == ')' || iter[0] == ';')) {

            int eend = iter - liter[0].begin() + 1;
            ERROR::GERROR(GERRMSG_INVALID_OPERATOR_FORMAT, filename, line, liter, iter, ebegin, eend);

        }

        tok.pos.second = iter - liter[0].begin();
        return tok;

    } else {

        while (iter[0] >= '!' && iter[0] <= '~' &&
            iter[0] != '"' && iter[0] != '\''
        ) {

            if (1 < tok.str.size()) {
                break;
            }
            
            if (iter[0] == '[' || iter[0] == ']' || iter[0] == '{' || iter[0] == '}' || iter[0] == '(' || iter[0] == ')') {
                tok.str.push_back(iter[0]);
                iter++;
                break;
            }

            tok.str.push_back(iter[0]);
            iter++;

        }
        
        if (tokenmap[tok.str]) {
            tok.tok = tokenmap[tok.str];
            tok.pos.second = iter - liter[0].begin();
            return tok;
        } else {
            int eend = iter - liter[0].begin() + 1;
            ERROR::GERROR(GERRMSG_UNKNOWN_OPERATOR, filename, line, liter, iter, ebegin, eend);
            tok.pos.second = iter - liter[0].begin();
            return tok;
        }

    }

}

std::vector<token> Lexer::lex() {

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
        std::cout << cnt.str << ":" << cnt.tok << ":" << cnt.line << ":" << ERROR::POSTOSTR(cnt.pos.first, cnt.pos.second) << std::endl;
    }

    return this->tokens;

}