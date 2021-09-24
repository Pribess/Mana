// Copyright (c) 2021 Heewon Cho

#include <iostream>
#include <fstream>
#include <getopt.h>

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

enum mode {
    Compile,
    Interpret
};

typedef struct rst {
    mode mmode;
    std::string filename;
} rst;

rst argparse(int argc, char **argv) {

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

    rst ret;

    ret.mmode = Compile;

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
                ret.mmode = Interpret;
                break;
        }
    }
    
    return ret;
}

int main(int argc, char **argv) {
    rst env = argparse(argc, argv);
    return 0;
}