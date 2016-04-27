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
            return 0;
        }
        //separate line into individual tokens
        tokens = seperateIntoTokens(js);
        int i;
        if (tokens.size() > 0) {
            ASTNode *node;
            node = parse(tokens);
            if (node != NULL) {
                Token *test = interp(node, environ);
                if (test) cout << test->getVal() << endl;
            }
        }
    }
}
