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
    Token(string val, string ty, int line, int startingPos, int endingPos) {
        value = val;
        type = ty;
        line = line;
        startingPos = startingPos;
        endingPos = endingPos;
    }
    string getVal(){
        return value;
    }

    string getType() {
        return type;
    }
private:
    string value;
    string type;
    int line, startingPos, endingPos;


};


class Integer : public Token {
public:
    Integer(string val, int line, int startingPos, int endingPos): Token(val, "Integer" ,line, startingPos, endingPos) {
        value = atoi(val.c_str());
    }
    int getVal(){
        return value;
    }

private:
    int value;

};

class Float : public Token {
public:
    Float(string val, int line, int startingPos, int endingPos): Token(val, "Float", line, startingPos, endingPos) {
        value = atof(val.c_str());
    }
    float getVal(){
        return value;
    }
private:
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
    }
private:

};

class ArithOperator: public Operator {
public:
    ArithOperator(string val, int line, int startingPos, int endingPos): Token(val, "ArithOperator", line, startingPos, endingPos){

    }
private:

};

class AssignmentOperator: public: Operator {
public:
    AssignmentOperator(string val, int line, int startingPos, int endingPos): Token(val, "AssignmentOperator", line, startingPos, endingPos){

    }
};

class LogicalOperator: public: Operator {
public:
    LogicalOperator(string val, int line, int startingPos, int endingPos): Token(val, "LogicalOperator", line, startingPos, endingPos){

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
    Function(string nm, vector <string> args, string def, int line, int startingPos, int endingPos): Token(name, "Function", line, startingPos, endingPos) {
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
