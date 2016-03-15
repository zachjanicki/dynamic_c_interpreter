// Some type checking functions...

using namespace std;

#include "typeChecking.h"

bool isInt(Token token) {
    string tokenString = token.getVal();
    regex regularExpression("^[+-]?(\d)+$|^\d+$");
    if (regex_match(tokenString, regularExpression)) {
        return true;
    }
    return false;
}

bool isFloat(Token token) {
    string tokenString = token.getVal();
    regex regularExpression("^[-+]?([0-9]*\.[0-9]+$|[0-9]+\.[0-9]*$");
    if (regex_match(tokenString, regularExpression)) {
        return true;
    }
    return false;
}

bool isOperator(Token token) {
    string tokenString = token.getVal();
    regex regularExpression("^[+-/*<>]{1}$|^(<=)$|^(>=)$|^(eq)$");
    if (regex_match(tokenString, regularExpression)) {
        return true;
    }
    return false;
}

bool isVariable(Token token) {
    string tokenString = token.getVal();
    regex regularExpression("^[a-zA-Z_]+$");
    if (regex_match(tokenString, regularExpression)) {
        return true;
    }
    return false;
}


bool isKeyword(Token token) {
    string tokenString = token.getVal();
    // if tokenString is in the keyword dictionary...
}
