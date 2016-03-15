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
    public :
    Token(string val, string ty) {
        value = val;
        type = ty;
    }
    private :
    string value;
    string type;
    
};


class Integer : public Token {
    public :
    Integer(string val) {
        value = atoi(val.c_str());
    }
    
    private :
    int value;
};

class Float : public Token {
    public :
    Float(string val) {
        value = atof(val.c_str());
    }
    private :
    float value;
    
};

class Symbol : public Token {
    public :
    Symbol(string val) {
        value = val;
    }
    private :
    string value;
    
};

class Operator : public Token {
    public :
    Operator(string val) {
        value = val;
    }
    private :
    string value;
    
    
};

class Variable : public Token {
    public :
    Variable(string val) {
        value = val;
    }
    private :
    string value;
    
};

class Keyword : public Token {
    public :
    Keyword(string val) {
        value = val;
    }
    private :
    string value;
    
};

class Function : public Token {
    public :
    Function(string nm, vector <string> args, string def) {
        name = nm;
        arguments = args;
        definition = def;
    }
    private :
    string name;
    vector<string> arguments;
    string definition;
    
};



#endif
