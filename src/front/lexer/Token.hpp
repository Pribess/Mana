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
    Pop,

    Import,
    As,
    From,

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
    OpIAdd,
    OpFAdd,
    OpDAdd,

    OpSub,
    OpISub,
    OpFSub,
    OpDSub,

    OpMul,
    OpIMul,
    OpFMul,
    OpDMul,

    OpDiv,
    OpIDiv,
    OpFDiv,
    OpDDiv,

    OpLcpy,
    OpRcpy,

    LogicEqual,
    LogicNotEqual,
    LessThanSign,
    GreaterThanSign,
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
    Double,
    Let,
    Const,

    Semicolon
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
    {"import", Token::Import},
    {"as", Token::As},
    {"from", Token::From},

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
    {"+i", Token::OpIAdd},
    {"+f", Token::OpFAdd},
    {"+d", Token::OpDAdd},

    {"-", Token::OpSub},
    {"-i", Token::OpISub},
    {"-f", Token::OpFSub},
    {"-d", Token::OpDSub},

    {"*", Token::OpMul},
    {"*i", Token::OpIMul},
    {"*f", Token::OpFMul},
    {"*d", Token::OpDMul},

    {"/", Token::OpDiv},
    {"/i", Token::OpIDiv},
    {"/f", Token::OpFDiv},
    {"/d", Token::OpDDiv},
    
    {"<-", Token::OpLcpy},
    {"->", Token::OpRcpy},

    {"==", Token::LogicEqual},
    {"!=", Token::LogicNotEqual},
    {"<", Token::LessThanSign},
    {">", Token::GreaterThanSign},
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
    {"double", Token::Double},
    
    {"let", Token::Let},
    {"const", Token::Const},

    {";", Token::Semicolon}
};

typedef struct token {
    Token tok;
    std::string str;
    int line;
    std::pair<int, int> pos;
} token;

#endif