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

void ERROR::GERROR(const char *type, std::string filename, int line, std::vector<std::string>::iterator &liter, std::string::iterator &iter, int ebegin, int eend) {
    std::string msg;
    msg.append(filename);
    msg.append(":");
    msg.append(ERROR::POSTOSTR(line, ebegin + 1));
    msg.append(BOLDRED);
    msg.append("error: ");
    msg.append(RESET);
    msg.append(type);
    msg.append("\n");
    msg.append("    ");
    msg.push_back((line) + 48);
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