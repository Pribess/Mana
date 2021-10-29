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
        std::cout << line << std::endl;
    }

    std::vector<std::string>::iterator iter = lines.begin();

    

}