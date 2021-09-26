// Copyright (c) 2021 Heewon Cho

#include "Error.hpp"

std::string Error::GETPOS(std::string::iterator iter, std::string *src) {
    int row = 1;
    int col = 1;

    for (int cnt = 0 ; cnt < src->size() ; cnt++) {
        if (cnt == iter - src->begin()) {
            std::string ret;
            char buff[128];


            std::sprintf(buff, "%d", row);
            ret.append(buff);
            ret.append(":");
            std::sprintf(buff, "%d", col);
            ret.append(buff);
            ret.append(":");
            ret.append(" ");
            
            return ret;
        }

        if (src->at(cnt) == '\n') {
            row++;
            col = 1;
        }

        col++;
    }

    return std::string("");
}