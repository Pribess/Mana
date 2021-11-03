// Copyright (c) 2021 Heewon Cho

#include "Error.hpp"

std::string ERROR::POSTOSTR(int row, int col) {

    std::string ret;

    char buff[256];

    std::memset(buff, 0, sizeof(buff));
    std::sprintf(buff, "%d", row);
    ret.append(buff);
    ret.append(":");

    std::memset(buff, 0, sizeof(buff));
    std::sprintf(buff, "%d", col);
    ret.append(buff);
    ret.append(": ");

    return ret;

}

void ERROR::ERROR(std::string str) {
    std::cout << str << std::endl;
}
void ERROR::GERROR(std::string filename, std::string pos, std::string str) {
    std::cout << filename << ":" << pos << BOLDRED << "fatal error: " << RESET << str << std::endl;
}