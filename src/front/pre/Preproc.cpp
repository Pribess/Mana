// Copyright (c) 2021 Heewon Cho

#include "Preproc.hpp"

Preproc::Preproc(std::string file) {
    this->file = file;
}

std::string Preproc::run() {
    return this->file;
}