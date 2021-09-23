// Copyright (c) 2021 Heewon Cho

#ifndef TOKEN_HPP
#define TOKEN_HPP

#include <map>
#include <string>

enum Token {
    Unknown,
    End,

    Number,
    String,
    Char,
    
    Word,

    If,
    Elif,
    Else,

    Switch,
    Case,

    Do,
    Again,
    While,

    BitAnd,
    BitOr,
    BitXor,
    BitNot,
    BitLShift,
    BitRShfit,

    OpAssignment,
    OpIncrement,
    OpDecrement,
    OpAdd,
    OpSub,
    OpMul,
    OpDiv,
    OpMod,

    LogicEqual,
    LogicNotEqual,
    LogicAbove,
    LogicBelow,
    LogicAboveOrEqual,
    LogicBelowOrEqual,
    LogicAnd,
    LogicOr,

    Comma,
    Colon,
    Semicolon,
    LParen,
    RParen,
    LBrace,
    RBrace,
    LBracket,
    RBracket
};

enum class CharType {
    Unknown,
    WhiteSpace,
    NumberLiteral,
    StringLiteral,
    Identifier,
    Operator
};

static std::map<std::string, Token> tokenmap = {
    {},
    {}
};

#endif