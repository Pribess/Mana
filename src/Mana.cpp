// Copyright (c) 2021 Heewon Cho

#include <iostream>
#include <getopt.h>

void argparse(int argc, char **argv) {

    static option optlist[] =  {
        {"version", no_argument, NULL, 'v'},
        {"interpret", no_argument, NULL, 'i'}
    };

    int opt;
    int optidx;

    while ((opt = getopt_long(argc, argv, "vi", optlist, &optidx)) != -1) {
        switch (opt) {
            case 'v':
                    std::cout <<
                    PROJECT_NAME << " version " << PROJECT_VERSION << std::endl << __VERSION__ << " " << __TIMESTAMP__
                    << std::endl;
                break;
            case 'i':
                break;
        }
    }
}

int main(int argc, char **argv) {
    argparse(argc, argv);
    return 0;
}