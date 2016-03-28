// Some type checking functions...

using namespace std;

#include "typeChecking.h"

bool isInt(string token) {
    regex regularExpression("^[+-]?[0-9]+$|^[0-9]+$");
    if (regex_match(token, regularExpression)) {
        return true;
    }
    return false;
}

bool isFloat(string token) {
    regex regularExpression("^[-+]?[0-9]*\\.[0-9]+$|[0-9]+\\.[0-9]*$");
    if (regex_match(token, regularExpression)) {
        return true;
    }
    return false;
}

bool isOperator(string token) {
    regex regularExpression("^[+-/*<>]{1}$|^(<=)$|^(>=)$|^(eq)$");
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


bool isKeyword(string token) {
    // if token is in the keyword dictionary...
    return true;
}
