// repl.cpp
// started 3/16/16
// main program function

#include <vector>
#include "Token.h"
#include "tokenize.h"
#include "Parser.h"
#include "env.h"

int main() {
    string js;
    vector<Token*> tokens;
    while (true) {
        // REPL!!
        cout << "js-> ";
        getline(cin, js);
        if (js == "exit") {
            break;
        }

        tokens = seperateIntoTokens(js);
        int i;
        for (i = 0; i < tokens.size(); i++) {
            cout << tokens[i]->getVal() << " " << tokens[i]->getType() << endl;
        }

        env *environ = new env; 
        ASTNode *node;
        node = parse(tokens);
        cout << "Root: " << node->token->getVal() << endl; 
        printTree(node);

    }
}
