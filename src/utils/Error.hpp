// Copyright (c) 2021 Heewon Cho

#ifndef ERROR_HPP
#define ERROR_HPP

#include <string>
#include <iostream>
#include <cstring>
#include <vector>

#define RESET   "\033[0m"
#define BLACK   "\033[30m"      /* Black */
#define RED     "\033[31m"      /* Red */
#define GREEN   "\033[32m"      /* Green */
#define YELLOW  "\033[33m"      /* Yellow */
#define BLUE    "\033[34m"      /* Blue */
#define MAGENTA "\033[35m"      /* Magenta */
#define CYAN    "\033[36m"      /* Cyan */
#define WHITE   "\033[37m"      /* White */
#define BOLDBLACK   "\033[1m\033[30m"      /* Bold Black */
#define BOLDRED     "\033[1m\033[31m"      /* Bold Red */
#define BOLDGREEN   "\033[1m\033[32m"      /* Bold Green */
#define BOLDYELLOW  "\033[1m\033[33m"      /* Bold Yellow */
#define BOLDBLUE    "\033[1m\033[34m"      /* Bold Blue */
#define BOLDMAGENTA "\033[1m\033[35m"      /* Bold Magenta */
#define BOLDCYAN    "\033[1m\033[36m"      /* Bold Cyan */
#define BOLDWHITE   "\033[1m\033[37m"      /* Bold White */

namespace ERROR {
    std::string POSTOSTR(int row, int col);
    void GERROR(const char *type, std::string filename, int line, std::vector<std::string>::iterator &liter, std::string::iterator &iter, int ebegin, int eend);
};

#define GERRMSG_INVALID_CONSTANT_FORMAT     "invalid constant format"
#define GERRMSG_INVALID_IDENTIFIER_FORMAT   "invalid identifier format"
#define GERRMSG_INVALID_KEYWORD_FORMAT      "invalid keyword format"
#define GERRMSG_INVALID_OPERATOR_FORMAT     "invalid operator format"
#define GERRMSG_KEYWORD_MISSING_LPAREN      "missing ( character after keyword"
#define GERRMSG_KEYWORD_MISSING_RPAREN      "missing terminating scope with ) character"
#define GERRMSG_MISSING_ARG_KEYWORD         "missing argument in keyword"
#define GERRMSG_MISSING_DOUBLE_QUOTE_END    "missing terminating \" character"
#define GERRMSG_MISSING_SINGLE_QUOTE_END    "missing terminating \' character"
#define GERRMSG_MISSING_GREATERTHENSIGN     "missing terminating < scope"
#define GERRMSG_UNKNOWN_OPERATOR            "unknown operator"

#endif