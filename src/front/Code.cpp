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

            token tok;
            tok.tok = Token::Unknown;

            if (iter[0] == ' ' || iter[0] == '\t' || iter[0] == '\r') {

                iter++;

            } else if (iter[0] >= '0' && iter[0] <= '9') {
                
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

                            std::string msg;
                            msg.append(this->filename);
                            msg.append(":");
                            msg.append(ERROR::POSTOSTR((liter - lines.begin()) + 1, ebegin + 1));
                            msg.append(BOLDRED);
                            msg.append("error: ");
                            msg.append(RESET);
                            msg.append(GERRMSG_INVALID_CONSTANT_FORMAT);
                            msg.append("\n");
                            msg.append("    ");
                            msg.push_back(((liter - lines.begin()) + 1) + 48);
                            msg.append(" | ");
                            for (int cnt = 0 ; cnt < liter[0].size() ; cnt++) {
                                if (cnt == ebegin) {
                                    msg.append(BOLDRED);
                                } else if (cnt == eend) {
                                    msg.append(RESET);
                                }
                                msg.push_back(liter[0].begin()[cnt]);
                            }
                            throw std::runtime_error(msg);

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

                            std::string msg;
                            msg.append(this->filename);
                            msg.append(":");
                            msg.append(ERROR::POSTOSTR((liter - lines.begin()) + 1, ebegin + 1));
                            msg.append(BOLDRED);
                            msg.append("error: ");
                            msg.append(RESET);
                            msg.append(GERRMSG_INVALID_CONSTANT_FORMAT);
                            msg.append("\n");
                            msg.append("    ");
                            msg.push_back(((liter - lines.begin()) + 1) + 48);
                            msg.append(" | ");
                            for (int cnt = 0 ; cnt < liter[0].size() ; cnt++) {
                                if (cnt == ebegin) {
                                    msg.append(BOLDRED);
                                } else if (cnt == eend) {
                                    msg.append(RESET);
                                }
                                msg.push_back(liter[0].begin()[cnt]);
                            }
                            throw std::runtime_error(msg);

                        }

                        tok.str.push_back(iter[0]);
                        iter++;

                    }

                } else {
                    // dec (default)

                    while (iter[0] >= '0' && iter[0] <= '9') {

                        tok.str.push_back(iter[0]);
                        iter++;

                    }

                }

                this->tokens.push_back(tok);

            } else if (iter[0] == '\"') {

                tok.tok = Token::String;
                int ebegin = iter - liter[0].begin();
                
                tok.str.push_back('"');
                iter++;

                while (iter[0] >= ' ' && iter[0] <= '~' && iter[0] != '\"') {
                    tok.str.push_back(iter[0]);
                    iter++;
                }

                if (iter[0] != '\"') {
                    int eend = iter - liter[0].begin() + 1;
                    
                    std::string msg;
                    msg.append(this->filename);
                    msg.append(":");
                    msg.append(ERROR::POSTOSTR((liter - lines.begin()) + 1, ebegin + 1));
                    msg.append(BOLDRED);
                    msg.append("error: ");
                    msg.append(RESET);
                    msg.append(GERRMSG_MISSING_DOUBLE_QUOTE_END);
                    msg.append("\n");
                    msg.append("    ");
                    msg.push_back(((liter - lines.begin()) + 1) + 48);
                    msg.append(" | ");
                    for (int cnt = 0 ; cnt < liter[0].size() ; cnt++) {
                        if (cnt == ebegin) {
                            msg.append(BOLDRED);
                        } else if (cnt == eend) {
                            msg.append(RESET);
                        }
                        msg.push_back(liter[0].begin()[cnt]);
                    }
                    throw std::runtime_error(msg);
                }

                tok.str.append("\"");

                this->tokens.push_back(tok);

                iter++;

            } else if (iter[0] == '\'') {
                
                tok.tok = Token::Char;
                int ebegin = iter - liter[0].begin();

                iter++;

                while (iter[0] >= ' ' && iter[0] <= '~' && iter[0] != '\'') {
                    tok.str.push_back(iter[0]);
                    iter++;
                }

                if (iter[0] != '\'') {
                    int eend = iter - liter[0].begin() + 1;
                    
                    std::string msg;
                    msg.append(this->filename);
                    msg.append(":");
                    msg.append(ERROR::POSTOSTR((liter - lines.begin()) + 1, (iter - liter[0].begin()) + 1));
                    msg.append(BOLDRED);
                    msg.append("error: ");
                    msg.append(RESET);
                    msg.append(GERRMSG_MISSING_SINGLE_QUOTE_END);
                    msg.append("\n");
                    msg.append("    ");
                    msg.push_back(((liter - lines.begin()) + 1) + 48);
                    msg.append(" | ");
                    for (int cnt = 0 ; cnt < liter[0].size() ; cnt++) {
                        if (cnt == ebegin) {
                            msg.append(BOLDRED);
                        } else if (cnt == eend) {
                            msg.append(RESET);
                        }
                        msg.push_back(liter[0].begin()[cnt]);
                    }
                    throw std::runtime_error(msg);
                }

                tok.str.append("\'");
                iter++;

                this->tokens.push_back(tok);

            }

        }

        liter++;

    }

    for (auto cnt : this->tokens) {
        std::cout << cnt.str << ":" << cnt.tok << std::endl;
    }

}