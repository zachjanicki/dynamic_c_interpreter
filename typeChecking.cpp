/* Implementation of typeChecking.h */

using namespace std;

#include "typeChecking.h"
#include "env.h"

bool isInt(string token) {
    regex regularExpression("^[+-]?[0-9]+$|^[0-9]+$");
    if (regex_match(token, regularExpression)) {
        return true;
    }
    return false;
}

bool isFloat(string token) {
    regex regularExpression("^[-]?[0-9]*\\.?[0-9]*|\\.");//[0-9]+\\.[0-9]*$");
    if (regex_match(token, regularExpression)) {
        return true;
    }
    return false;
}
/* deprecated
bool isOperator(string token) {
    regex regularExpression("^[+-*<>]{1}$|^(<=)$|^(>=)$|^(eq)$");
    if (regex_match(token, regularExpression)) {
        return true;
    }
    return false;
} */

bool isArithOperator(string token) {
    regex regularExpression("^[+-/*%]{1}$|^\\+\\+$|^--$|^\\+=$|^-=$|^\\*=$|^/=$");
    if (regex_match(token, regularExpression)) {
        return true;
    }
    return false;
}

bool isLogicalOperator(string token) {
    regex regularExpression("^[<>]{1}$|^==$|^<=$|^>=$|^!=$");
    if (regex_match(token, regularExpression)) {
        return true;
    }
    return false;
}

bool isAssignmentOperator(string token) {
    regex regularExpression("^=$");
    if (regex_match(token, regularExpression)) {
        return true;
    }
    return false;
}

bool isVariable(string token) {
    regex regularExpression("^[a-zA-Z_]+$");
    if (regex_match(token, regularExpression)) {
        return true;
    }
    return false;
}

bool isScopeSym(string token) {
    regex regularExpression("^[\\[\\]()]$");
    if (regex_match(token, regularExpression)) {
        return true; 
    }
    else return false; 
}

bool isSemiColon(string token) {
    regex regularExpression("^;$");
    if (regex_match(token, regularExpression)) {
        return true;
    }
    return false;
}

bool isKeyword(string token) {
    // if token is in the keyword dictionary...
    env *environ = new env();
    if (std::find(environ->keywords.begin(), environ->keywords.end(), token) != environ->keywords.end())
    return true; 
}

bool isSameType(Token *token1, Token *token2) {
    if (token1 == NULL || token2 == NULL) {
        return false;
    }

    return (token1->getType() == token2->getType());
}
