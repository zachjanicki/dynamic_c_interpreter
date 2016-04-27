// tokenize.cpp
// tokenize function implementation
#include "tokenize.h"
#include <vector>
#include "typeChecking.h"
#include "Token.h"
#include <stdlib.h>

//checks the type of a token
string checkType(string token) {
    if (isInt(token)) {
        return "Int";
    } else if  (isString(token)){
        return "String";
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
    } else if (isScopeSym(token)) {
        return "Scope Symbol";
    } else {
        return "Undefined Token Type";
    }
}


//breaks a string into a vector of token pointers
vector<Token*> seperateIntoTokens(string line) {
    //a=1;
    //a = 1;
    string characters = "";

    //list of tokens created by this function
    vector<Token*> tokenList;
    //return if the line is empty
    if (line.length() == 0) return tokenList;
    //create pointer to 2 tokens
    Token *oldToken;
    Token *newToken;
    oldToken = NULL;
    int begin = 0;
    //scan through entire line character by character
    for (int i = 0; i < line.length(); i++) {
        //check for a space
        if (line[i] != ' ') { // dealing with characters right next to each other "aabbas;, a=1, var==var2, ect..."
            //check for a string and handle
            if (line[i] ==  '"' or line[i] == '\''){
                char firstChar = line[i];
                int startingPos = i;
                int currentPos = i;
                characters = line[currentPos];
                currentPos++;
                while (currentPos != line.length()){
                    if (line[currentPos] == firstChar){
                        characters += firstChar;
                        currentPos++;
                        break;

                    }
                    characters += line[currentPos];
                    currentPos++;
                }
                if (currentPos == line.length() && line[currentPos - 1] != firstChar){
                    cout <<  "Error: String Incomplete" << endl;
                    return tokenList;
                }
                else {
                    //create a string token 
                    newToken = createToken(characters, 0, startingPos, currentPos - 1);
                    tokenList.push_back(newToken);
                    begin = currentPos;
                    i = currentPos - 1;
                    //reset the two token pointers
                    newToken = NULL;
                    oldToken = NULL;
                    //reset the token characters
                    characters = "";
                }

            }
            //if the token is NOT a string continue here
            else {
                //get the token starting position
                int startingPos = i - characters.length();
                //add the current char to the characters for the current token
                characters += line[i];
                int endingPos = i;
                //create a new token, point newToken pointer to it
                newToken = createToken(characters, 0, startingPos, endingPos);

                //check to see if last token is of different type than new token (unless we are on the first char)
                if (!isSameType(newToken, oldToken) && i != begin && (!newToken || (newToken->getType() != "LogicalOperator" && newToken->getType() != "Keyword"))) { // then we need to add what we have onto the tokenList
                    begin = i;
                    i--;

                    //push oldToken into the vector of token pointers
                    tokenList.push_back(oldToken);
                    //reset the newToken and oldToken pointers as well as characters string
                    newToken = NULL;
                    oldToken = NULL;
                    characters = "";

                }
                else {
                    //if they reach this point set the oldToken pointer to the newToken -> simply replace oldToken
                    oldToken = newToken;
                }
            }

        } else { //there is a space so we add what we have to the tokenList and reset the struct
            //if not null, add the oldToken and reset variables
            if (oldToken) tokenList.push_back(oldToken);
            newToken = NULL;
            oldToken = NULL;
            characters = "";
            begin = i+1;
        }
    }
    //if not null, add the oldToken and return the vector
    if (oldToken) tokenList.push_back(oldToken);
    return tokenList;
}



//creates a token based on type checking functions
Token* createToken(string TokenStr, int line, int start, int end) {

    //create token pointer
    Token *currentToken;
    //get the token type and create the appropriate subtoken
    if (isArithOperator(TokenStr)) {
        currentToken = new ArithOperator(TokenStr, line, start, end);
    }
    else if (isString(TokenStr)){
        currentToken = new String(TokenStr.substr(1, TokenStr.length() - 2), line, start, end);
    }
    else if (isFloat(TokenStr)) {
        currentToken = new Float(TokenStr, line, start, end);
    } else if (isLogicalOperator(TokenStr)) {
        currentToken = new LogicalOperator(TokenStr, line, start, end);
    } else if (isAssignmentOperator(TokenStr)) {
        currentToken = new AssignmentOperator(TokenStr, line, start, end);
    } else if (isKeyword(TokenStr)) {
        currentToken = new Keyword(TokenStr, line, start, end);
    } else if (isVariable(TokenStr)) {
        currentToken = new Variable(TokenStr, line, start, end);
    } else if (isSemiColon(TokenStr)) {
        currentToken = new Symbol(TokenStr, "Semicolon", line, start, end);
    } else if (isScopeSym(TokenStr)) {
        currentToken = new ScopeSym(TokenStr, line, start, end);
    }  else {
        currentToken = NULL;
    }

    //return the newly created token
    return currentToken;

}
