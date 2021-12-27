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

    Extern,

    If,
    Elif,
    Else,
    Endif,

    Do,
    Again,
    While,
    Break,

    BitAnd,
    BitOr,
    BitXor,
    BitNot,
    BitLShift,
    BitRShfit,

    OpAssignment,

    OpAddress,
    OpReference,

    OpIncrement,
    OpDecrement,

    OpAdd,
    OpUAdd,
    OpFAdd,
    OpDAdd,

    OpSub,
    OpUSub,
    OpFSub,
    OpDSub,

    OpMul,
    OpUMul,
    OpFMul,
    OpDMul,

    OpDiv,
    OpUDiv,
    OpFDiv,
    OpDDiv,

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

    Double,
    Asm,

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

    {"extern", Token::Extern},

    {"if", Token::If},
    {"else if", Token::Elif},
    {"else", Token::Else},
    {"endif", Token::Endif},

    {"do", Token::Do},
    {"again", Token::Again},
    {"while", Token::While},
    {"break", Token::Break},

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
    {"+u", Token::OpUAdd},
    {"+f", Token::OpFAdd},
    {"+d", Token::OpDAdd},

    {"-", Token::OpSub},
    {"-u", Token::OpUSub},
    {"-f", Token::OpFSub},
    {"-d", Token::OpDSub},

    {"*", Token::OpMul},
    {"*u", Token::OpUMul},
    {"*f", Token::OpFMul},
    {"*d", Token::OpDMul},

    {"/", Token::OpDiv},
    {"/i", Token::OpUDiv},
    {"/f", Token::OpFDiv},
    {"/d", Token::OpDDiv},
    
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

    {"double", Token::Double},
    {"asm", Token::Asm},
    
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