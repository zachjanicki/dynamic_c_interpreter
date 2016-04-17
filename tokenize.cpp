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
    if (line.length() == 0) return tokenList;
    Token *oldToken;
    Token *newToken;
    oldToken = NULL;
    int begin = 0;
    cout << line << endl;
    for (int i = 0; i < line.length(); i++) {
        if (line[i] != ' ') { // dealing with characters right next to each other "aabbas;, a=1, var==var2, ect..."
            characters += line[i];
            int startingPos = i - characters.length();
            int endingPos = i;
            newToken = createToken(characters, 0, startingPos, endingPos);
            if (!isSameType(newToken, oldToken) && i != begin && newToken->getType() != "LogicalOperator") { // then we need to add what we have onto the tokenList
                if (!newToken || newToken->getType() != "Keyword") {
                    begin = i;
                    i--;
                    tokenList.push_back(oldToken);
                    newToken = NULL;
                    oldToken = NULL;
                    characters = "";

                }
            }
            else {
                oldToken = newToken;

            }


        } else { //there is a space so we add what we have to the tokenList and reset the struct
            tokenList.push_back(oldToken);
            newToken = NULL;
            oldToken = NULL;
            characters = "";
            begin = i+1;
        }
    }

    tokenList.push_back(oldToken);
    return tokenList;
}



////need a way to pass in line, startingPos, endingPos when creating token objects.
Token* createToken(string TokenStr, int line, int start, int end) {

    Token *currentToken;
    /*if (isInt(TokenStr)) {
        currentToken = new Integer();
    }*/

    if (isFloat(TokenStr)) {
        currentToken = new Float(TokenStr, line, start, end);
    } else if (isArithOperator(TokenStr)) {
        currentToken = new ArithOperator(TokenStr, line, start, end);
    } else if (isLogicalOperator(TokenStr)) {
        currentToken = new LogicalOperator(TokenStr, line, start, end);
    } else if (isAssignmentOperator(TokenStr)) {
        currentToken = new AssignmentOperator(TokenStr, line, start, end);
    } else if (isVariable(TokenStr)) {
        currentToken = new Variable(TokenStr, line, start, end);
    } else if (isSemiColon(TokenStr)) {
        currentToken = new Symbol(TokenStr, line, start, end);
    } else if (isKeyword(TokenStr)) {
        currentToken = new Keyword(TokenStr, line, start, end);
    } else {
        currentToken = NULL;
    }

    return currentToken;

}
