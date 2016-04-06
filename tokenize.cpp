// tokenize.cpp
// tokenize function implementation
#include "tokenize.h"
#include <vector>
#include "typeChecking.h"
#include "Token.h"

string checkType(string token) {
    if (isInt(token)) {
        return "Int";
    } else if (isFloat(token)) {
        return "Float";
    } else if (isArithOperator(token)) {
        return "Arith Operator";
    } else if (isLogicalOperator(token)) {
        return "Logical Operator";
    } else if (isAssignmentOperator(token)) {
        return "Assignment Operator";
    } else if (isVariable(token)) {
        return "Variable";
    } else if (isSemiColon(token)) {
        return "Semicolon";
    } else if (isKeyword(token)) {
        return "Keyword";
    } else {
        return "Undefined Token Type";
    }
}

vector<Token*> seperateIntoTokens(string line) {
    //a=1;
    //a = 1;
    string characters;
    vector<Token*> tokenList;
    Token *oldToken;
    Token *newToken;
    int i;
    for (i = 0; i < line.length(); i++) {
        oldToken = NULL;
        if (line[i] != ' ') { // dealing with characters right next to each other "aabbas;, a=1, var==var2, ect..."
            characters += line[i];
            newToken = createToken(characters);

            if (!isSameType(newToken, oldToken) && i != 0) { // then we need to add what we have onto the tokenList
                if (!newToken.getType() != "Keyword") {
                    i--;
                    tokenList.pushback(oldToken);
                    newToken = NULL;
                    oldToken = NULL;
                    characters = "";
                }
            }
            else {
                oldToken = newToken;
            }


        } else { //there is a space so we add what we have to the tokenList and reset the struct
            tokenList.pushback(oldToken);
            newToken = NULL;
            oldToken = NULL;
            characters = "";
        }
    }
    return tokenList;
}



////need a way to pass in line, startingPos, endingPos when creating token objects.
Token* createToken(string TokenStr) {

    Token *currentToken;
    if (isInt(current)) {
        currentToken = new Integer();
    } else if (isFloat(current)) {
        currentToken = new Float();
    } else if (isArithOperator(current)) {
        currentToken = new ArithOperator();
    } else if (isLogicalOperator(current)) {
        currentToken = new LogicalOperator();
    } else if (isAssignmentOperator(current)) {
        currentToken = new AssignmentOperator();
    } else if (isVariable(current)) {
        currentToken = new Variable();
    } else if (isSemiColon(current)) {
        currentToken = new Symbol();
    } else if (isKeyword(current)) {
        currentToken = new Keyword();
    } else {
        currentToken = NULL;
    }

    return currentToken;

}
