//
//  Token.h
//
//
//  Created by John Joyce on 3/15/16.
//
//

#ifndef Token_h
#define Token_h

#include <stdio.h>
#include <iostream>
#include <string>
#include <cstring>
#include <vector>


using namespace std;

class Token {
public:
    Token(){
        value = "0";
        type = "Token";
        line = 0;
        startingPos = 0;
        endingPos = 0;
    }
    Token(string val, string ty, int ln, int startingP, int endingP) {
        value = val;
        type = ty;
        line = ln;
        startingPos = startingP;
        endingPos = endingP;

    }
    Token& operator=( Token &token){
        value = token.value;
        type = token.type;
        line = token.line;
        startingPos = token.startingPos;
        endingPos = token.endingPos;
        return *this;
    }
    string getVal(){
        return value;
    }

    string getType() {
        return type;
    }
    int getLine(){
        return line;
    }
    int getStartingPos(){
        return startingPos;
    }
    int getEndingPos(){
        return endingPos;
    }
    virtual int getPrecedence(){
        return precedence;
    }

    string value;
    string type;
    int line, startingPos, endingPos, precedence;


};


class Integer : public Token {
public:
    Integer(string val, int line, int startingPos, int endingPos): Token(val, "Integer" ,line, startingPos, endingPos) {
        value = atoi(val.c_str());
    }

    Integer& operator=( Integer &token){
        value = token.value;
        type = token.type;
        line = token.line;
        startingPos = token.startingPos;
        endingPos = token.endingPos;
        return *this;
    }
    int getVal(){
        return value;
    }

    int value;

};

class Float : public Token {
public:
    Float(string val, int line, int startingPos, int endingPos): Token(val, "Float", line, startingPos, endingPos) {
        value = atof(val.c_str());
    }

    Float& operator=( Float &token){
        value = token.value;
        type = token.type;
        line = token.line;
        startingPos = token.startingPos;
        endingPos = token.endingPos;
        return *this;
    }
    float getVal(){
        return value;
    }
    float value;

};

class Symbol : public Token {
public:
    Symbol(string val, int line, int startingPos, int endingPos): Token(val, "Symbol", line, startingPos, endingPos) {
    }

private:

};

class Operator : public Token {
public:
    Operator(string val, string type, int line, int startingPos, int endingPos): Token(val,type, line, startingPos, endingPos) {
        if (val == "+" || val == "-"){
            precedence = 0;
        }
        else if (val == "*" || val == "/"){
            precedence = 1;

        }
    }
    virtual int getPrecedence(){
        return precedence;
    }
    Operator& operator=( Operator &token){
        value = token.value;
        type = token.type;
        line = token.line;
        startingPos = token.startingPos;
        endingPos = token.endingPos;
        precedence = token.precedence;
        return *this;
    }
private:

};

class ArithOperator: public Operator {
public:

    ArithOperator(string val, int line, int startingPos, int endingPos): Operator(val, "ArithOperator", line, startingPos, endingPos){

    }

private:
    int precedence;

};

class AssignmentOperator: public Operator {
public:
    AssignmentOperator(string val, int line, int startingPos, int endingPos): Operator(val, "AssignmentOperator", line, startingPos, endingPos){

    }
};

class LogicalOperator: public Operator {
public:
    LogicalOperator(string val, int line, int startingPos, int endingPos): Operator(val, "LogicalOperator", line, startingPos, endingPos){

    }
};



class Variable : public Token {
public:
    Variable(string val, int line, int startingPos, int endingPos): Token(val, "Variable", line, startingPos, endingPos) {
    }
private:

};

class Keyword : public Token {
public:
    Keyword(string val, int line, int startingPos, int endingPos):Token(val, "Keyword", line, startingPos, endingPos)  {
    }
private:

};

class Function : public Token {
public:
    Function(string nm, vector <string> args, string def, int line, int startingPos, int endingPos): Token(nm, "Function", line, startingPos, endingPos) {
        name = nm;
        arguments = args;
        definition = def;
    }
private:
    string name;
    vector<string> arguments;
    string definition;

};



#endif
