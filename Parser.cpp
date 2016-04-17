
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
using namespace std;


ASTNode* parse(vector <Token *> tokens){
    vector <ASTNode*> nodes;
    int prevIndex;
    for (int i = 0; i < tokens.size(); i++){
        ASTNode* newNode = new ASTNode; 
        newNode->token = tokens[i];
        newNode->left = NULL;
        newNode->right = NULL;
        if (nodes.size() && i != 1){

        }
        if (newNode->token->getType() != "ArithOperator" && newNode->token->getType() != "LogicalOperator" && newNode->token->getType() != "AssignmentOperator" ){
            if (newNode->token->getVal() == "var") continue; 
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
                if (temp->token->getType() == "ArithOperator" || temp->token->getType() == "LogicalOperator" || temp->token->getType() == "AssignmentOperator")  
                    temp->right = newNode; 
                else {
                    if (prevNode->token->getType() == "ArithOperator" || newNode->token->getType() == "LogicalOperator" || newNode->token->getType() == "AssignmentOperator" ){
                        if (prevNode->right == NULL)
                        prevNode->right = newNode;
                        else {
                            cout << "Error" << endl; 
                        }

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
                   // cout << prevNode->token->getVal() << " < " << newNode->token->getVal() << endl; 
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
