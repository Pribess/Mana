// Copyright (c) 2021 Heewon Cho

#include "Error.hpp"

std::string ERROR::GETROW(int idx, std::string code) {

    std::string ret;

    int row = 1;

    for (int cnt = 0 ; cnt < idx ; cnt++) {

        if (code.at(cnt) == '\n') {
            row++;
        }

    }

    char buff[256];

    std::sprintf(buff, "%d", row);
    ret.append(buff);
    ret.append(":");

    return ret;

}

void ERROR::ERROR(std::string str) {
    std::cout << str << std::endl;
}
void ERROR::GERROR(std::string filename, std::string pos, std::string str) {
    std::cout << filename << ":" << pos << BOLDRED << "fatal error: " << RESET << str << std::endl;
}