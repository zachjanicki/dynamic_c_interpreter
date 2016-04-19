// repl.cpp
// started 3/16/16
// main program function

#include <vector>
#include "Token.h"
#include "tokenize.h"
#include "Parser.h"
#include "env.h"

int main() {
    //input line
    string js;
    //vector containing input tokens
    vector<Token*> tokens;
    while (true) {
        // REPL!!
        cout << "JS-> ";
        getline(cin, js);
        if (js == "exit") {
            break;
        }
        //separate line into individual tokens
        tokens = seperateIntoTokens(js);
        int i;
        for (i = 0; i < tokens.size(); i++) {
          //  cout << tokens[i]->getVal() << " " << tokens[i]->getType() << endl;
        }
        if (tokens.size() > 0) {
            env *environ = new env; 
            ASTNode *node;
            node = parse(tokens);
            if (node != NULL) {
                cout << "Root: " << node->token->getVal() << endl; 
                printTree(node);
            }   
        }
    }
}
