// Copyright (c) 2021 Heewon Cho

#include <iostream>
#include <getopt.h>

void credit() {
    std::cout 
    << PROJECT_NAME << " version " << PROJECT_VERSION << std::endl 
    << __VERSION__ << " " << __TIMESTAMP__ << std::endl;
}

enum mode {
    Compile,
    Interpret
};

typedef struct {
    mode mmode;

} rst;

rst argparse(int argc, char **argv) {

    static option optlist[] =  {
        {"version", no_argument, NULL, 'v'},
        {"interpret", no_argument, NULL, 'i'}
    };

    int opt;
    int optidx;

    rst ret;

    while ((opt = getopt_long(argc, argv, "vi", optlist, &optidx)) != -1) {
        switch (opt) {
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
    argparse(argc, argv);
    return 0;
}