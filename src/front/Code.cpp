// Copyright (c) 2021 Heewon Cho

#include <front/Code.hpp>

Code::Code(std::string filename, std::string code) {
    this->filename = filename;
    this->code = code;
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

            if (iter[0] == ' ' || iter[0] == '\t' || iter[0] == '\r') {

                iter++;

            } else if ((iter[0] >= 'A' && iter[0] <= 'Z') || (iter[0] >= 'a' && iter[0] <= 'z')) {

                std::string rst;

                while ((iter[0] >= 'A' && iter[0] <= 'Z') || (iter[0] >= 'a' && iter[0] <= 'z') || (iter[0] >= '0' && iter[0] <= '9')) {

                    rst.push_back(iter[0]);
                    iter++;

                }

                if (tokenmap[rst]) {
                    this->tokens.push_back(token{tokenmap[rst], rst});
                } else {
                    this->tokens.push_back(token{Token::Identifier, rst});
                }

            } else if (iter[0] >= '0' && iter[0] <= '9') {

                std::string rst;

                while (iter[0] >= '0' && iter[0] <= '9') {

                    rst.push_back(iter[0]);
                    iter++;

                }

                this->tokens.push_back(token{Token::Number, rst});

            } else if (iter[0] == '\"') {

                std::string rst("\"");

                iter++;

                while (iter[0] >= ' ' && iter[0] <= '~' && iter[0] != '\"') {
                    rst.push_back(iter[0]);
                    iter++;
                }

                if (iter[0] != '\"') {
                    std::string msg;
                    msg.append(this->filename);
                    msg.append(":");
                    msg.append(ERROR::POSTOSTR((liter - lines.begin()) + 1, (iter - liter[0].begin()) + 1));
                    msg.append(BOLDRED);
                    msg.append("error: ");
                    msg.append(RESET);
                    msg.append(GERRMSG_MISSING_DOUBLE_QUOTE_END);
                    throw std::runtime_error(msg);
                }

                rst.append("\"");

                this->tokens.push_back(token{Token::String, rst});

                iter++;

            } else if (iter[0] == '\'') {

                std::string rst("\'");

                iter++;

                while (iter[0] >= ' ' && iter[0] <= '~' && iter[0] != '\'') {
                    rst.push_back(iter[0]);
                    iter++;
                }

                if (iter[0] != '\'') {
                    std::string msg;
                    msg.append(this->filename);
                    msg.append(":");
                    msg.append(ERROR::POSTOSTR((liter - lines.begin()) + 1, (iter - liter[0].begin()) + 1));
                    msg.append(BOLDRED);
                    msg.append("error: ");
                    msg.append(RESET);
                    msg.append(GERRMSG_MISSING_SINGLE_QUOTE_END);
                    throw std::runtime_error(msg);
                }

                rst.append("\'");
                iter++;

                this->tokens.push_back(token{Token::Char, rst});

            } else if ((iter[0] >= '!' && iter[0] <= '/') || (iter[0] >= ':' && iter[0] <= '@') || (iter[0] >= '[' && iter[0] <= '`') || (iter[0] >= '{' && iter[0] <= '~')
                && iter[0] != '"' && iter[0] != '\''
            ) {

                int ebegin = iter - liter[0].begin();

                std::string rst;
                rst.push_back(iter[0]);
                iter++;

                if (rst != "[" && rst != "]" && rst != "(" && rst != ")" && rst != "{" && rst != "}" && rst != "<" && rst != ">") {

                    while (iter[0] >= '!' && iter[0] <= '~' &&
                        iter[0] != '"' && iter[0] != '\''
                    ) {

                        rst.push_back(iter[0]);
                        iter++;

                    }

                }

                int eend = iter - liter[0].begin();

                if (tokenmap[rst]) {
                    this->tokens.push_back(token{tokenmap[rst], rst});
                } else {
                    std::string msg;
                    msg.append(this->filename);
                    msg.append(":");
                    msg.append(ERROR::POSTOSTR((liter - lines.begin()) + 1, (iter - liter[0].begin()) + 1));
                    msg.append(BOLDRED);
                    msg.append("error: ");
                    msg.append(RESET);
                    msg.append(GERRMSG_UNKNOWN_OPERATOR);
                    msg.append("\n");
                    msg.append("    ");
                    msg.push_back(((liter - lines.begin()) + 1) + 48);
                    msg.append(" | ");
                    for (int cnt ; cnt < liter[0].size() ; cnt++) {
                        if (cnt == ebegin) {
                            msg.append(BOLDRED);
                        } else if (cnt == eend) {
                            msg.append(RESET);
                        }
                        msg.push_back(liter[0].begin()[cnt]);
                    }
                    throw std::runtime_error(msg);
                }

            } else {
                std::string msg;
                msg.append(this->filename);
                msg.append(":");
                msg.append(ERROR::POSTOSTR((liter - lines.begin()) + 1, iter - liter[0].begin()));
                msg.append(BOLDRED);
                msg.append("error: ");
                msg.append(RESET);
                msg.append("unknown character '");
                msg.push_back(iter[0]);
                msg.append("'");
                std::cout << msg << std::endl;
                throw std::runtime_error(msg);
            }
            
        }

        liter++;

    }

    for (auto cnt : this->tokens) {
        std::cout << cnt.str << ":" << cnt.tok << std::endl;
    }

}