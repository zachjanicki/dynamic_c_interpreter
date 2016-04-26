
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

//parses the text based on a vector of token pointers
ASTNode* parse(vector <Token *> tokens){
    vector <ASTNode*> nodes;
    int prevIndex;
    stack<Token*> scopeStack;
    for (int i = 0; i < tokens.size(); i++){
        /* ------- CREATE NEW ASTNode --------- */
        ASTNode* newNode; 
        Token *current = tokens[i];
        //end of statements
        if (current->getVal() == ";" ) return nodes[0];
        else newNode = new ASTNode;
        newNode->left = NULL;
        newNode->right = NULL;
        newNode->leftcenter = NULL;
        newNode->rightcenter = NULL;
        newNode->token = tokens[i];

        //get previous node
        prevIndex = nodes.size()-1;
        ASTNode *prevNode;
        if (nodes.size() > 0) prevNode = nodes[prevIndex];


        /* -------- PARSE --------- */
        if (newNode->token->getType() != "Keyword" && newNode->token->getType() != "ArithOperator" && newNode->token->getType() != "LogicalOperator" && newNode->token->getType() != "AssignmentOperator" ){
            /* ---------- DEALS WITH SCOPE OPERATORS '(' AND '[' ------------ */
            if (tokens[i]->getType() == "Scope Symbol" && tokens[i]->getPrecedence() == 0) {
                scopeStack.push(tokens[i]);
                vector<Token*>subTokens;
                int j = i+1;
                while (!scopeStack.empty() && j < tokens.size()) {

                    //check that there are more tokens
                    if (tokens[j]) subTokens.push_back(tokens[j]);
                    else { error("Syntax Error: Misplaced Separator"); return NULL; }

                    if (tokens[j]->getType() == "Scope Symbol") {
                        if (tokens[j]->getPrecedence() == 0)
                            scopeStack.push(tokens[j]);
                        else {
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




                if (!scopeStack.empty()) { error("Syntax Error: Unbalanced separators"); return NULL; }
                subTokens.pop_back();

                i = j-1;

                if (prevNode->token->getVal() == "for" && prevNode->rightcenter == NULL) {
                    ASTNode* forCondition = parse(subTokens);
                    prevNode->rightcenter = forCondition;
                    continue;
                }

                newNode = parse(subTokens);
                newNode->token->precedence = 5;

            }
                /* ---------- END SCOPE HANDLING ----------- */

            if (nodes.size() == 0){
                nodes.push_back(newNode);
            }
            else{
                if (prevNode->left == NULL && prevNode->token->getVal() != "-") {
                    prevNode->left = newNode;
                }
                else {
                    //check right side for placement
                    while (prevNode->right != NULL)
                        prevNode = prevNode->right;

                    if (prevNode->left == NULL && prevNode->token->getVal() == "-") {
                        Token *prevToken = prevNode->token;
                        Token *newToken = newNode->token;
                        string minus = "-";
                        Token *tempToken = new Float(minus.append(newToken->getVal()), newToken->getLine(), newToken->getStartingPos(), newToken->getEndingPos());
                        delete prevToken;
                        prevNode->token = tempToken;
                        continue;
                    }

                    //if we have an if statement, use the center node
                    if (prevNode->token->getVal() == "if") {
                            if (prevNode->leftcenter == NULL) prevNode->leftcenter = newNode;
                            else if (prevNode->right == NULL) prevNode->right = newNode;
                            else {
                                error("Syntax Error: Exiting parser.");
                                return NULL;
                            }
                        }
                    //if not an if statement use right child
                    else {
                        if (prevNode->right == NULL)
                            prevNode->right = newNode;
                        else {
                            error("Syntax Error: Exiting parser.");
                            return NULL;
                        }
                    }
                }
            }
        }
        //if a keyword
        else if (newNode->token->getType() == "Keyword"){
            //check if variable
            if (newNode->token->getVal() == "var") continue;
            //check for if
            if (newNode->token->getVal() == "else") {
                if (prevNode->token->getVal() == "if") continue;
                else {
                    error("Syntax Error: Invalid Keyword");
                    return NULL;
                }
            }
            if (nodes.size() == 0) nodes.push_back(newNode);
            else error("Syntax Error: Invalid Keyword");

        }
        //if an operator
        else {
            //if begins with an operator, something is wrong
            if (nodes.size() == 0){
                if (newNode->token->getVal() != "-") {
                    error("Syntax Error: Invalid operator");
                    return NULL;
                }
                else {
                    nodes.push_back(newNode);
                }
            }
            else if (prevNode->token->getType() != "ArithOperator" && prevNode->token->getType() != "LogicalOperator" && prevNode->token->getType() != "AssignmentOperator"){
                if (newNode->token->getVal() == "=" && prevNode->token->getType() == "Float") { error("Syntax Error: Literals are unassigable"); return NULL;}
                newNode->left = prevNode;
                nodes[prevIndex] = newNode;
            }
            else{
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
