// repl.cpp
// started 3/16/16
// main program function


#include "Token.h"
#include <vector>
int main() {
    string js;
    vector<Token> tokens;
    while (true) {
        // REPL!!
        cout << "js-> ";
        cin >> js;
        if (js == "exit") {
            break;
        }
        //tokens = js.tokenize() //or tokenize(js) ? depends on how we write that

    }
}
