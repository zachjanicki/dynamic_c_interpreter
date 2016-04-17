//
//  Parser.h
//
//
//  Created by Pierce Cunneen on 4/10/2016
//
//

#ifndef Parser_h
#define Parser_h

struct ASTNode{
    ASTNode *left;
    ASTNode *right;
    Token *token;
};



ASTNode* parse(vector <Token *> tokens);

void printTree(ASTNode *node);


#endif
