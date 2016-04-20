
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
using namespace std;


ASTNode* parse(vector <Token *> tokens){
    vector <ASTNode*> nodes;
    int prevIndex;
    stack<Token*> scopeStack; 
    for (int i = 0; i < tokens.size(); i++){

        /* ------- CREATE NEW ASTNode --------- */
        ASTNode* newNode; 
        Token *current = tokens[i]; 
        if (current->getVal() == ";" ) return nodes[0]; 
        else newNode = new ASTNode; 
        newNode->left = NULL;
        newNode->right = NULL;
        newNode->center = NULL; 
        newNode->token = tokens[i];

        /* -------- PARSE --------- */
        if (newNode->token->getType() != "Keyword" && newNode->token->getType() != "ArithOperator" && newNode->token->getType() != "LogicalOperator" && newNode->token->getType() != "AssignmentOperator" ){
            if (newNode->token->getVal() == "var") continue;  

            /* ---------- DEALS WITH SCOPE OPERATORS '(' AND '[' ------------ */
            if (tokens[i]->getType() == "Scope Symbol" && tokens[i]->getPrecedence() == 0) {
                if (tokens[i]->getVal() == "{" && nodes[0]->token->getType() != "Keyword") { error("Syntax Error: Invalid separators"); return NULL; }
                scopeStack.push(tokens[i]);
                vector<Token*>subTokens; 
                int j = i+1; 
                while (!scopeStack.empty() && j < tokens.size()) {
                    subTokens.push_back(tokens[j]); 
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
                    j++; 

                }

                if (j > tokens.size()) { error("Syntax Error: Unbalanced separators"); return NULL; }
                subTokens.pop_back(); 
                newNode = parse(subTokens);
                newNode->token->precedence = 5; 
                i = j-1; 
            }
                /* ---------- END SCOPE HANDLING ----------- */

            if (nodes.size() == 0){
                nodes.push_back(newNode);
            }
            else{
                prevIndex = nodes.size() -1;
                ASTNode *prevNode;
                prevNode = nodes[prevIndex];
                ASTNode* temp = prevNode;
                if (temp->left == NULL) temp->left = newNode; 
                else {
                    while (temp->right != NULL)
                        temp = temp->right; 
                    if (temp->token->getType() == "ArithOperator" || temp->token->getType() == "LogicalOperator" || temp->token->getType() == "AssignmentOperator" ){
                        if (temp->right == NULL)
                            temp->right = newNode;
                        else {
                            error("Syntax Error: Exiting parser.");
                            return NULL; 
                        }
                    }
                    else if (temp->token->getType() == "Keyword") {
                        if (temp->token->getVal() == "if") {
                            if (temp->center == NULL) temp->center = newNode;  
                            else if (temp->right == NULL) temp->right = newNode; 
                            else {
                                error("Syntax Error: Exiting parser.");
                                return NULL; 
                            }
                        }
                    }
                }
                
            }
        }
        //if an operator
        else if (newNode->token->getType() == "Keyword"){ 
            if (newNode->token->getVal() == "else" || newNode->token->getVal() == "var") continue; 
            if (nodes.size() == 0) nodes.push_back(newNode); 
            else error("Syntax Error: Invalid Keyword");

        }
        else {
            if (nodes.size() == 0){
                error("Syntax Error: Invalid operator");
                return NULL; 
            }
            prevIndex = nodes.size() -1 ;
            ASTNode *prevNode;
            prevNode = nodes[prevIndex];
            if (prevNode->token->getType() != "ArithOperator" && prevNode->token->getType() != "LogicalOperator" && prevNode->token->getType() != "AssignmentOperator"){
                newNode->left = prevNode;
                nodes[prevIndex] = newNode;
            }
            else{
                if (prevNode->token->getPrecedence() < newNode->token->getPrecedence()){

                    ASTNode *tempNode;
                    tempNode = prevNode;
                    newNode->left = tempNode->right;
                    tempNode->right = newNode;
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

void error(string message) {
    cout << message << endl; 
}


void printTree(ASTNode *node){
    if (node != NULL){
        printTree(node -> left);
        cout << node -> token->getVal() << endl;
        printTree(node->center); 
        printTree(node -> right);
    }


}
