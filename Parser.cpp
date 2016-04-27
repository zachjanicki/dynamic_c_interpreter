
//
//  Parser.cpp
//
//
//  Created by Pierce Cunneen on 4/10/2016
//
//

#include <math.h>
#include <string>
#include <vector>
#include "Token.h"
#include "Parser.h"
#include <stack>
#include "tokenize.h"
using namespace std;

//parses the text based on a vector of token pointers passed in - returns the root node of the abstract syntax tree
ASTNode* parse(vector <Token *> tokens){
    //create a temporary structure to hold the nodes
    vector <ASTNode*> nodes;
    int prevIndex;
    //create a stack to maintain the parenthetic scope
    stack<Token*> scopeStack;

    //scan through each token in the passed in vector
    for (int i = 0; i < tokens.size(); i++){
        /* ------- CREATE NEW ASTNode --------- */
        //create a new node
        ASTNode* newNode;
        //snag a token pointer from the vector
        Token *current = tokens[i];
        //handle end of statements
        if (current->getVal() == ";" ) return nodes[0];
        else newNode = new ASTNode;

        //initialize the new AST node
        newNode->left = NULL;
        newNode->right = NULL;
        newNode->leftcenter = NULL;
        newNode->rightcenter = NULL;
        newNode->token = tokens[i];

        //get previous node in the vector previously created, if there is one
        prevIndex = nodes.size()-1;
        ASTNode *prevNode = NULL; 
        if (nodes.size() > 0) prevNode = nodes[prevIndex];


        /* -------- PARSE --------- */

        //if the new node token is anything other than a keyword or operator enter here
        if (newNode->token->getType() != "Keyword" && newNode->token->getType() != "ArithOperator" && newNode->token->getType() != "LogicalOperator" && newNode->token->getType() != "AssignmentOperator" ){
            /* ---------- DEALS WITH SCOPE OPERATORS '(' '{' and '[' ------------ */
            //if the token is an opening parenthesis symbol, enter here
            if (tokens[i]->getType() == "Scope Symbol" && tokens[i]->getPrecedence() == 0) {
                //push the symbol onto a stack
                scopeStack.push(tokens[i]);
                //create vector of tokens within the new scope
                vector<Token*>subTokens;
                int j = i+1;

                //scan through until closing brace is found
                while (!scopeStack.empty() && j < tokens.size()) {

                    //check that there are more tokens
                    if (tokens[j]) subTokens.push_back(tokens[j]);
                    else { error("Syntax Error: Misplaced Separator"); return NULL; }

                    //check if closing brace has been found
                    if (tokens[j]->getType() == "Scope Symbol") {
                        if (tokens[j]->getPrecedence() == 0)
                            scopeStack.push(tokens[j]);
                        else {
                            //check for incorrect closing brace -- if correct closing brace found, pop the opening brace
                            if (scopeStack.top()->getVal() == "[") {
                                if (tokens[j]->getVal() == "]") scopeStack.pop();
                                else { error("Syntax Error: Unbalanced separators"); return NULL; }
                            }
                            else if (scopeStack.top()->getVal() == "(") {
                                if (tokens[j]->getVal() == ")") scopeStack.pop();
                                else { error("Syntax Error: Unbalanced separators"); return NULL; }
                            }
                            else {
                                if (tokens[j]->getVal() == "}") scopeStack.pop();
                                else { error("Syntax Error: Unbalanced separators"); return NULL; }
                            }
                        }
                    }
                    //handle if a semicolon has been reached - of particular importance in 'for' loop
                    else if (tokens[j]->getType() == "Semicolon" && prevNode->token->getVal() == "for") {
                        if (prevNode->left == NULL) {   
                            ASTNode* forCondition = parse(subTokens);
                            prevNode->left = forCondition;
                            subTokens.clear();
                        }
                        else if (prevNode->leftcenter == NULL) {
                            ASTNode* forCondition = parse(subTokens);
                            prevNode->leftcenter = forCondition;
                            subTokens.clear();
                        }

                    }
                    j++;
                }

                //if there are still braces on the stack, something is wrong
                if (!scopeStack.empty()) { error("Syntax Error: Unbalanced separators"); return NULL; }
                subTokens.pop_back();

                //reset the incrementer value to appropriate place
                i = j-1;

                //check if we are building a for loop tree
                if (prevNode != NULL && prevNode->token->getVal() == "for" && prevNode->rightcenter == NULL) {
                    //parse the for loop condition
                    ASTNode* forCondition = parse(subTokens);
                    prevNode->rightcenter = forCondition;
                    continue;
                }

                //if not a for loop, simply parse whatever is inside the brackets
                newNode = parse(subTokens);
                //set high precedence for anything inside parenthesis so that is appears at bottom of tree
                newNode->token->precedence = 5;

            }
                /* ---------- END SCOPE HANDLING ----------- */

            //if there are no nodes on the tree yet, push the current token into the vector
            if (nodes.size() == 0){
                nodes.push_back(newNode);
            }
            else{
                //if the previous node is an operator other than subtraction sign simply assign its child
                if (prevNode->left == NULL && prevNode->token->getVal() != "-") {
                    prevNode->left = newNode;
                }
                else {
                    //check right side for placement -- scan to bottom of current tree
                    while (prevNode->right != NULL)
                        prevNode = prevNode->right;

                    //handle the negative sign on doubles --- it is not subtraction
                    if (prevNode->left == NULL && prevNode->token->getVal() == "-") {
                        Token *prevToken = prevNode->token;
                        Token *newToken = newNode->token;
                        string minus = "-";
                        Token *tempToken = new Float(minus.append(newToken->getVal()), newToken->getLine(), newToken->getStartingPos(), newToken->getEndingPos());
                        delete prevToken;
                        prevNode->token = tempToken;
                        continue;
                    }

                    //if we have an if statement previously
                    if (prevNode->token->getVal() == "if") {
                            //if there is no body, point to leftcenter 
                            if (prevNode->leftcenter == NULL) prevNode->leftcenter = newNode;
                            //if there is a body but no else body, point to right
                            else if (prevNode->right == NULL) prevNode->right = newNode;
                            //otherwise something went wrong with the if-else statement
                            else {
                                error("Syntax Error: Invalid Keyword");
                                return NULL;
                            }
                        }
                    //if not an if statement use right child
                    else {
                        //always point to right child if not an if-else 
                        if (prevNode->right == NULL)
                            prevNode->right = newNode;
                        else {
                            error("Syntax Error: Invalid Keyword");
                            return NULL;
                        }
                    }
                }
            }
        }
        //if a keyword token
        else if (newNode->token->getType() == "Keyword"){
            //check if variable -- if so, simply continue to the next token
            if (newNode->token->getVal() == "var") continue;
            //check for if-else statement by keyword
            if (newNode->token->getVal() == "else") {
                if (prevNode->token->getVal() == "if") continue;
                else {
                    error("Syntax Error: Invalid Keyword");
                    return NULL;
                }
            }
            //if we have a keyword and the size on the nodes stack is not 0, throw an error, otherwise push 
            if (nodes.size() == 0) nodes.push_back(newNode);
            else error("Syntax Error: Invalid Keyword");

        }
        //if newnode is an operator 
        else {
            //if begins with an operator other than - (negative), something is wrong, throw an error
            if (nodes.size() == 0){
                if (newNode->token->getVal() != "-") {
                    error("Syntax Error: Invalid operator");
                    return NULL;
                }
                else {
                    //if a negative symbol, push back the operator
                    nodes.push_back(newNode);
                }
            }
            //if the vector has nodes 
            else if (prevNode->token->getType() != "ArithOperator" && prevNode->token->getType() != "LogicalOperator" && prevNode->token->getType() != "AssignmentOperator"){
                if (newNode->token->getVal() == "=" && prevNode->token->getType() == "Float") { error("Syntax Error: Literals are unassigable"); return NULL;}
                newNode->left = prevNode;
                nodes[prevIndex] = newNode;
            }
            else{
                //check the precedence of two operators if they are next to each other -- whichever has higher significance should go on the bottom
                if (prevNode->token->getPrecedence() <= newNode->token->getPrecedence()){
                    newNode->left = prevNode->right;
                    prevNode->right = newNode;
                }
                else {
                    newNode->left = prevNode;
                    nodes[prevIndex] = newNode;
                }

            }

        }

    }
    return nodes[0];
}




//prints a specific error message
void error(string message) {
    cout << message << endl;
}

//prints the AST
void printTree(ASTNode *node){
    if (node != NULL){
        printTree(node -> left);
        cout << node -> token->getVal() << endl;
        printTree(node->leftcenter);
        printTree(node->rightcenter);
        printTree(node -> right);
    }
}
