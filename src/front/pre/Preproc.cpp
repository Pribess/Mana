// Copyright (c) 2021 Heewon Cho

#include "Preproc.hpp"

Preproc::Preproc(std::string file) {
    this->file = file;
}

std::string Preproc::import(std::string origin, std::string::iterator iter, std::string dir) {

    dir.append(".ma");
    std::fstream file(dir);

    if (!file) {
        GERROR(GETPOS(iter, origin) ,dir << ": No such file or directory");
        exit(1);
    }

    std::stringstream ss;
    std::string ret = origin;

    ss << file;

    ret.erase(iter, iter + 7);
    ret.insert(iter, ss.str());

    return ret;
}

std::string Preproc::run() {

    std::string::iterator iter = this->file.begin();

    bool isdliteral = false;
    bool issliteral = false;

    for (int cnt = 0 ; cnt < this->file.size() ; cnt++) {

        if (*iter == '"' && !issliteral) {
            isdliteral = !isdliteral;
        }

        if (*iter == '\'' && !isdliteral) {
            issliteral = !issliteral;
        }

        if (isdliteral || issliteral) {
            continue;
        }

        if (*iter == '#') {
            switch (*(iter + 1)) {
                case 'i':

                    break;
            }
        }

        iter++;
    }

    return this->file;
}