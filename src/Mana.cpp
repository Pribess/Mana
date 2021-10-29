// Copyright (c) 2021 Heewon Cho

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>

#include "Version.hpp"

#include "utils/data/Keyvalue.hpp"
#include "front/Code.hpp"

void help() {
    std::cout <<
    "usage: mana <option> <file>\n" <<
    std::endl <<
    "--version, -v      see current version\n" <<
    "-o <file>          launch interpreting mode\n" <<
    "-s                 skip assemble step\n" <<
    std::endl <<
    "\"mana --help\" and \"mana -h\" list available option" <<
    std::endl;
    exit(0);
}

void version() {
    std::cout
    << "mana version " << VERSION << std::endl
    << __VERSION__ << " " << __TIMESTAMP__ << 
    std::endl;
    exit(0);
}

std::vector<std::string> argparse(int argc, char **argv) {

    std::vector<std::string> filelist;
    std::vector<std::string> args;

    for (int cnt = 0 ; cnt < argc ; cnt++) {
        args.push_back(argv[cnt]);
    }

    Keyvalue::SetKey(ASSEMBLE, "true");

    std::vector<std::string>::iterator iter = args.begin() + 1;
    
    while (true) {

        if (iter[0].front() == '-') {
            if (iter[0] == "-h") {
                help();
            } else if (iter[0] == "-v" || iter[0] == "--version") {
                version();
            } else if (iter[0] == "-o") {
                if (iter[1] == "") {
                    std::string msg;
                    msg.append("mana: ");
                    msg.append(BOLDRED);
                    msg.append("error: ");
                    msg.append(RESET);
                    msg.append("missing filename after '-o'");
                    throw std::runtime_error(msg);
                }

                Keyvalue::SetKey(TARGET, iter[1]);
                iter++;
            } else if (iter[0] == "-s") {
                Keyvalue::SetKey(ASSEMBLE, "false");
            } else {
                std::string msg;
                msg.append("mana: ");
                msg.append(BOLDRED);
                msg.append("error: ");
                msg.append(RESET);
                msg.append("unrecognized option '");
                msg.append(iter[0]);
                msg.append("'");
                throw std::runtime_error(msg);
            }
        } else {
            filelist.push_back(iter[0]);
        }

        if (Keyvalue::GetKey(TARGET) == "" && Keyvalue::GetKey(ASSEMBLE) == "false") {
            std::string msg;
            msg.append("mana: ");
            msg.append(BOLDRED);
            msg.append("error: ");
            msg.append(RESET);
            msg.append("cannot make a meaningless skip assemble on interpret mode");
            throw std::runtime_error(msg);
        }

        iter++;

        if (iter == args.end()) {
            break;
        }

    }

    return filelist;
}

class Mana {
    private:
        std::vector<std::string> filelist;

    public:
        Mana(std::vector<std::string> filelist) {
            this->filelist = filelist;
        };

        void run() {
            std::ifstream ifs(filelist.at(0));
            std::stringstream ss;

            ss<<ifs.rdbuf();

            Code c(filelist.at(0), ss.str());
            c.Tokenize();
        }

};

int main(int argc, char **argv) {

    try {
        Mana mana(argparse(argc, argv));
        mana.run();
    } catch (std::runtime_error &e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }

    return 0;
}
