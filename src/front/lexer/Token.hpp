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
    
    Identifier,

    If,
    Elif,
    Else,
    Endif,

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
    OpFDiv,
    OpMod,
    OpLcpy,
    OpRcpy,

    LogicEqual,
    LogicNotEqual,
    LogicAbove,
    LogicBelow,
    LogicAboveOrEqual,
    LogicBelowOrEqual,
    LogicAnd,
    LogicOr,

    Comma,
    LParen,
    RParen,
    LBrace,
    RBrace,
    LBracket,
    RBracket,

    Float,
    New,
};

enum class CharType {
    Unknown,
    WhiteSpace,
    NumberLiteral,
    StringLiteral,
    Controller,
    Identifier,
    Operator,
    Keyword
};

static std::map<std::string, Token> tokenmap = {
    {"#Unknown", Token::Unknown},
    {"#End", Token::End},

    {"#Number", Token::Number},
    {"#String", Token::String},
    {"#Char", Token::Char},
    
    {"#Identifier", Token::Identifier},

    {"if", Token::If},
    {"else if", Token::Elif},
    {"else", Token::Else},
    {"endif", Token::Endif},

    {"switch", Token::Switch},
    {"#case", Token::Case},

    {"do", Token::Do},
    {"again", Token::Again},
    {"while", Token::While},

    {"&", Token::BitAnd},
    {"|", Token::BitOr},
    {"^", Token::BitXor},
    {"~", Token::BitNot},
    {"<<", Token::BitLShift},
    {">>", Token::BitRShfit},

    {"=", Token::OpAssignment},
    {"++", Token::OpIncrement},
    {"--", Token::OpDecrement},
    {"+", Token::OpAdd},
    {"-", Token::OpSub},
    {"*", Token::OpMul},
    {"/", Token::OpDiv},
    {"/f", Token::OpFDiv},
    {"%", Token::OpMod},
    {"<-", Token::OpLcpy},
    {"->", Token::OpRcpy},

    {"==", Token::LogicEqual},
    {"!=", Token::LogicNotEqual},
    {"<", Token::LogicAbove},
    {">", Token::LogicBelow},
    {"<=", Token::LogicAboveOrEqual},
    {">=", Token::LogicBelowOrEqual},
    {"&&", Token::LogicAnd},
    {"||", Token::LogicOr},

    {",", Token::Comma},
    {"(", Token::LParen},
    {")", Token::RParen},
    {"{", Token::LBrace},
    {"}", Token::RBrace},
    {"[", Token::LBracket},
    {"]", Token::RBracket},

    {"float", Token::Float},
    {"new", Token::New},
};

#endif