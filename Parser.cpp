
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
    vector <ASTNode> nodes;
    int length;
    for (int i = 0; i < tokens.size(); i++){
        ASTNode newNode;
        newNode.token = *tokens[i];
        newNode.left = NULL;
        newNode.right = NULL;
        if (nodes.size() && i != 1){

        }
        if (newNode.token.getType() == "Float"){
            if (i == 0){
                nodes.push_back(newNode);
            }
            else{
                length = nodes.size() -1;
                ASTNode prevNode;
                prevNode = nodes[length];
                if (prevNode.token.getType() == "ArithOperator"){
                    prevNode.right = &newNode;

                }
            }
        }
        else if ( newNode.token.getType() == "ArithOperator" ) {
            if (nodes.size() == 0){
                throw "Error";
            }
            length = nodes.size() -1 ;
            ASTNode prevNode;
            prevNode = nodes[length];
            if (prevNode.token.getType() == "Float"){
                newNode.left = &prevNode;
                nodes[length] = newNode;

            }
            else if (prevNode.token.getType() == "ArithOperator"){
                if (prevNode.token.getPrecedence() < newNode.token.getPrecedence()){
                    ASTNode tempNode;
                    tempNode = prevNode;
                    newNode.left = tempNode.right;
                    prevNode.right = &newNode;
                }
                else {
                    ASTNode tempNode;
                    tempNode = prevNode;
                    newNode.left = &prevNode;
                    nodes[length] = newNode;

                }

            }

        }
    }
    return &nodes[0];



}


void printTree(ASTNode *node){
    if (node != NULL){
        printTree(node -> left);
        cout << node -> token.getVal() << endl;
        printTree(node -> right);
    }




}
