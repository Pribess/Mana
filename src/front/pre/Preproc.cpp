// Copyright (c) 2021 Heewon Cho

#include "Preproc.hpp"

Preproc::Preproc(std::string filename) {
    this->filename = filename;
    std::ifstream filestream(this->filename);

    if (filestream.fail()) {
        ERROR("mana: No such file or directory: " << this->filename);
        exit(1);
    }
    
    std::stringstream ss;
    ss << filestream.rdbuf();

    this->file = ss.str();
}

Preproc::Preproc(std::string filename, std::string filenameprev, std::string pos) {
    this->filename = filename;
    std::ifstream filestream(this->filename);

    if (filestream.fail()) {
        GERROR(filenameprev, pos, ": No such file or directory: " << this->filename);
        exit(1);
    }
    
    std::stringstream ss;
    ss << filestream.rdbuf();

    this->file = ss.str();
}

void Preproc::import(std::string::iterator begin, std::string::iterator end, std::string dir) {

    dir.append(".ma");

    Preproc *p = new Preproc(dir, this->filename, Error::GETPOS(begin, &this->file));

    this->file.replace(begin, end, p->run());
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
                    if (Utils::Hashx65599("import", 6) != Utils::Hashx65599(&(*(iter + 1)), 6)) {
                        GERROR(this->filename, Error::GETPOS(iter + 7 + cnt, &this->file), ": Unknown macro");
                        exit(1);
                    }

                    bool innamescope = false;

                    std::string dir;

                    for (int cnt = 0 ; cnt < this->file.size() ; cnt++) {

                        if (*(iter + 7 + cnt) != '<' && *(iter + 7 + cnt) != ' ') {
                            GERROR(this->filename, Error::GETPOS(iter + 7, &this->file), ": '<' character required");
                        }

                        if (*(iter + 7 + cnt) == '<' && !innamescope) {
                            innamescope = true;
                        }

                        if (*(iter + 7 + cnt) == '>') {
                            if (!innamescope) {
                                GERROR(this->filename, Error::GETPOS(iter + 7 + cnt, &this->file), ": '<' character required before '>'");
                                exit(1);
                            }

                            innamescope = false;
                            dir.erase(0, 1);

                            if (dir.size() == 0) {
                                GERROR(this->filename, Error::GETPOS(iter + 7 + cnt, &this->file), ": File name should be declared");
                            }

                            this->import(iter, iter + 8 + cnt, dir);
                            break;
                        }

                        if (innamescope) {
                            dir.push_back(*(iter + 7 + cnt));
                        }

                        if (cnt >= this->file.size() - 1) {
                            GERROR(this->filename, Error::GETPOS(iter + 7, &this->file), ": '>' character required");
                            exit(1);
                        }
                    }
                    break;
            }
        }

        iter++;
    }

    return this->file;
}