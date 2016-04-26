// repl.cpp
// started 3/16/16
// main program function

#include <vector>
#include "Token.h"
#include "tokenize.h"
#include "Parser.h"
#include "env.h"
#include "interp.h"

int main() {
    //input line
    string js;
    //vector containing input tokens
    vector<Token*> tokens;
    env *environ = new env;
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
          //cout << tokens[i]->getVal() << " " << tokens[i]->getType() << endl;
        }
        if (tokens.size() > 0) {

            ASTNode *node;
            node = parse(tokens);
            if (node != NULL) {
                cout << "Root: " << node->token->getVal() << endl;
                printTree(node);
                Token test = interp(node, environ);
                cout << test.getVal() << endl;
            }
        }
    }
}
