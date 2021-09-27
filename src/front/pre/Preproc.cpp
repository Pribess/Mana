// Copyright (c) 2021 Heewon Cho

#include "Preproc.hpp"

Preproc::Preproc(std::string filename) {
    this->filename = filename;
    std::ifstream filestream(this->filename);

    if (filestream.fail()) {
        ERROR("mana: No such file or directory: " << this->filename);
        exit(1);
    }
    
    std::getline(filestream, this->file);
}

void Preproc::import(std::string::iterator begin, std::string::iterator end, std::string dir) {

    dir.append(".ma");
    std::ifstream filestream(dir);

    if (filestream.fail()) {
        GERROR(this->filename, Error::GETPOS(begin, &this->file) , " " << dir << "" << ": No such file or directory");
        exit(1);
    }

    std::string importfile;
    std::getline(filestream, importfile);

    this->file.replace(begin, end, importfile);
    std::cout << "after imported \n"<< this->file<< std::endl;
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

                    for (int cnt = 0 ; ; cnt++) {
                        std::cout << *(iter + 7 +cnt) <<std::endl;

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
                            this->import(iter, iter + 7 + cnt, dir);
                            break;
                        }

                        if (innamescope) {
                            dir.push_back(*(iter + 7 + cnt));
                        }

                    }
                    break;
            }
        }

        iter++;
    }

    return this->file;
}