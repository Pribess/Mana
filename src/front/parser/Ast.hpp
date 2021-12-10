// Copyright (c) 2021 Heewon Cho

#ifndef AST_HPP
#define AST_HPP

#include <string>
#include <vector>

namespace ast {

struct Statement {};

struct DeclareFunction : Statement {
    std::string name;
    std::vector<std::string> params;
    std::vector<Statement> block;
};

struct Function : Statement {
    std::string name;
};

struct Call : Statement {
    Function *obj;
};

struct DeclareVariable : Statement {
    std::string name;
    std::string assign;
};

struct DeclareConstant : Statement {
    std::string name;
    std::string value;
};

struct StringLiteral : Statement {
    std::string value;
};

struct Literal : Statement {
    std::string value;
};

struct Variable : Statement {
    std::string name;
};

struct Constant : Statement {
    std::string name;
};

struct Push : Statement {
    Statement *obj;
};

struct Pop : Statement {
    Statement *obj;
};

struct Address : Statement {
    Variable *obj;
};

struct Reference : Statement {
    Variable *obj;
};

struct Asm : Statement {
    std::string code;
};

struct From : Statement {
    std::string from;
};

struct Import : Statement {
    std::vector<std::string> list;
    From *from;
};

};

#endif