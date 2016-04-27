//
//  Parser.h
//
//
//  Created by Pierce Cunneen on 4/10/2016
//
//
#ifndef Parser_h
#define Parser_h

//create the Abstract Syntax Tree Node class
class ASTNode {

public: 
	//left child of node
    ASTNode *left;
    //left center child of node
    ASTNode *leftcenter; 
    //right child of node
    ASTNode *right;
    //right center child of node
    ASTNode *rightcenter;
    //the token associated with the node
    Token *token;

};


ASTNode* parse(vector <Token *> tokens); //parses the vector of token pointers into an abstract syntax tree

void printTree(ASTNode *node);
void error(string message); 


#endif
