
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

        ASTNode* newNode = new ASTNode; 
        newNode->left = NULL;
        newNode->right = NULL;
        newNode->token = tokens[i];
        if (newNode->token->getType() != "ArithOperator" && newNode->token->getType() != "LogicalOperator" && newNode->token->getType() != "AssignmentOperator" ){
            if (newNode->token->getVal() == "var") continue;  
            if (tokens[i]->getType() == "Scope Symbol" && tokens[i]->getPrecedence() == 0) {
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
                                else cout << "Invalid separators error" << endl; 
                            }
                            else {
                                if (tokens[j]->getVal() == ")") scopeStack.pop(); 
                                else cout << "Invalid separators error" << endl; 
                            }
                        }
                    }
                    j++; 

                }
                if (j > tokens.size()) cout << "Invalid separators error"; 
                subTokens.pop_back(); 
                newNode = parse(subTokens);
                newNode->token->precedence = 5; 
                i = j-1; 
            }
            if (nodes.size() == 0){
                nodes.push_back(newNode);
            }
            else{
                prevIndex = nodes.size() -1;
                ASTNode *prevNode;
                prevNode = nodes[prevIndex];
                ASTNode* temp = prevNode;
                while (temp->right != NULL)
                    temp = temp->right; 
                if (temp->token->getType() == "ArithOperator" || temp->token->getType() == "LogicalOperator" || temp->token->getType() == "AssignmentOperator" ){
                    if (temp->right == NULL)
                        temp->right = newNode;
                    else {
                        cout << "Error" << endl; 
                    }
                }
                
            }
        }
        //if an operator
        else {
            if (nodes.size() == 0){
                throw "Error";
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


void printTree(ASTNode *node){
    if (node != NULL){
        printTree(node -> left);
        cout << node -> token->getVal() << endl;
        printTree(node -> right);
    }




}
