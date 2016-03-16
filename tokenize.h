// tokenize.h
// function definitions to break a line into tokens

#include <string>
#include "Token.h"
#include "typeChecking.h"

string checkType(Token token) {
    if (isInt(token)) {
        return "Int";
    } else if (isFloat(token)) {
        return "Float";
    } else if (isOperator(token)) {
        return "Operator";
    } else if (isVariable(token)) {
        return "Variable";
    } else if (isKeyword(token)) {
        return "Keyword";
    } else {
        return "Undefined Token Type";
    }
}
