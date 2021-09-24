// Copyright (c) 2021 Heewon Cho

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <getopt.h>

#include "utils/Keyvalue.hpp"

void credit() {
    std::cout 
    << PROJECT_NAME << " version " << PROJECT_VERSION << "\n"
    << __VERSION__ << " " << __TIMESTAMP__ << 
    std::endl;
}

void help() {
    std::cout << 
    "usage: mana <option> <file>\n" <<
    "\"mana --help\" and \"mana -h\" list available option\n" <<
    std::endl;

    std::cout <<
    "--version, -v      see current version\n" <<
    "--interpret, -i    launch interpreting mode\n" <<
    std::endl;
}

std::vector<std::string> argparse(int argc, char **argv) {

    if (argc < 2) {
        std::cout << 
        "usage: mana <option> <file>\n" <<
        "\"mana --help\" and \"mana -h\" list available option" <<
        std::endl;
        exit(1);
    }

    static option optlist[] =  {
        {"help", no_argument, NULL, 'h'},
        {"version", no_argument, NULL, 'v'},
        {"interpret", no_argument, NULL, 'i'}
    };

    int opt;
    int optidx;

    while ((opt = getopt_long(argc, argv, "hvi", optlist, &optidx)) != -1) {
        switch (opt) {
            case 'h':
                help();
                break;
            case 'v':
                credit();
                exit(0);
                break;
            case 'i':
                Keyvalue::SetKey("mode", "Interpret");
                break;
        }
    }
    
    std::vector<std::string> filelist;

    for (int cnt = 1 ; cnt < argc ; cnt++ ) {
        if (std::string(argv[cnt]).front() == '-') {
            continue;
        }
        filelist.push_back(argv[cnt]);
    }

    return filelist;
}

int main(int argc, char **argv) {
    std::vector<std::string> rst = argparse(argc, argv);
    
    return 0;
}