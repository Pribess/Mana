// Copyright (c) 2021 Heewon Cho

#include <iostream>
#include <vector>
#include <string>
#include <getopt.h>

#include "Driver.hpp"
#include "utils/data/Keyvalue.hpp"
#include "utils/Error.hpp"

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

    while ((opt = getopt_long(argc, argv, "hvio:", optlist, &optidx)) != -1) {
        switch (opt) {
            case 'h':
                help();
                break;
            case 'v':
                credit();
                exit(0);
                break;
            case 'i':
                Keyvalue::SetKey(mode, "Interpret");
                if (Keyvalue::GetKey(target) != "") {
                    ERROR::ERROR("Interpreting mode cannot run with -o option");
                    exit(1);
                }
                break;
            case 'o':
                if (Keyvalue::GetKey(mode) == "Interpret") {
                    ERROR::ERROR("-o option cannot declare with Interpreting mode");
                    exit(1);
                }
                Keyvalue::SetKey(target, optarg);
        }
    }
    
    std::vector<std::string> filelist;

    for (int cnt = 1 ; cnt < argc ; cnt++ ) {
        if (
            !std::string(argv[cnt]).starts_with("-") &&
            std::string(argv[cnt - 1]) != std::string("-o")
        ) {
            filelist.push_back(argv[cnt]);
        }
    }

    return filelist;
}

int main(int argc, char **argv) {

    std::vector<std::string> rst = argparse(argc, argv);

    Driver *driver = new Driver(rst);
    driver->run();
    delete driver;

    return 0;
}
