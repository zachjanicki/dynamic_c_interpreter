
#include "interp.h"
#include <typeinfo>


using namespace std;

Token* interp(ASTNode *root, env * environment) {
/* This function is very recursive. In the base case of a float or a string,
the current token is returned. The other cases depend on the type of current token */

    Token *result;
    Token *left;
    Token *right;

    if (!root) {
        return NULL;
    }
    if (root -> token -> getType() == "Float") {
        result = root -> token;
    } else if (root -> token -> getType() == "String"){
        result = root -> token;
    } else if (root -> token -> getType() == "Variable") {
        // either return the variable variable or give an error
        if (environment -> variables[root -> token -> getVal()]) {
            result = environment -> variables[root -> token -> getVal()];
        } else {
            cout << "Variable " << root -> token -> getVal() << " is not defined" << endl;
            return NULL;
        }

    } else if (root -> token -> getType() == "AssignmentOperator") {
        // update the current variable or create a new one
        delete environment -> variables[root -> left -> token -> getVal()];
        environment -> variables[root -> left -> token -> getVal()] = interp(root -> right, environment);
        return NULL;

    } else if (root -> token -> getType() == "ArithOperator") {
        /* check interpret the left side and the right side, and then apply the
        current operator */
        left = interp(root -> left, environment);
        right = interp(root -> right, environment);
        if (root -> token -> getVal() == "+") {
            if (left -> getType() == "String"){
                result = new Token(interp(root -> left, environment)->getVal() + interp(root -> right, environment)->getVal(), "String", 0, 0, 0);
            }
            else {
                result = new Token(to_string(stof(interp(root -> left, environment)->getVal()) + stof(interp(root -> right, environment)->getVal())), "Float", 0, 0, 0);
            }
        } else if (root -> token -> getVal() == "-") {
            result = new Token(to_string(stof(interp(root -> left, environment)->getVal()) - stof(interp(root -> right, environment)->getVal())), "Float", 0, 0, 0);
        } else if (root -> token -> getVal() == "*") {
            result = new Token(to_string(stof(interp(root -> left, environment)->getVal()) * stof(interp(root -> right, environment)->getVal())), "Float", 0, 0, 0);
        } else if (root -> token -> getVal() == "/") {
            result = new Token(to_string(stof(interp(root -> left, environment)->getVal()) / stof(interp(root -> right, environment)->getVal())), "Float", 0, 0, 0);
        } else if (root -> token -> getVal() == "%") {
            // bit of extra work happening to deal with mod so that we can mod floats also
            double a = stof(interp(root -> left, environment) -> getVal());
            double b = stof(interp(root -> right, environment) -> getVal());
            double modResult;
            while (a > b) {
                a = a - b;
            }
            modResult = a;
            result = new Token(to_string(modResult), "Float", 0, 0, 0);
        }

        else if (root->token->getVal() == "+=") {
            delete environment -> variables[root -> left -> token -> getVal()];
            environment -> variables[root -> left -> token -> getVal()] = new Token(to_string(stof(interp(root -> left, environment)->getVal()) + stof(interp(root -> right, environment)->getVal())), "Float", 0, 0, 0);
            return NULL;
        }
        else if (root->token->getVal() == "-=") {
            delete environment -> variables[root -> left -> token -> getVal()];
            environment -> variables[root -> left -> token -> getVal()] = new Token(to_string(stof(interp(root -> left, environment)->getVal()) - stof(interp(root -> right, environment)->getVal())), "Float", 0, 0, 0);
            return NULL;
        }
        else if (root->token->getVal() == "*=") {
            delete environment -> variables[root -> left -> token -> getVal()];
            environment -> variables[root -> left -> token -> getVal()] = new Token(to_string(stof(interp(root -> left, environment)->getVal()) * stof(interp(root -> right, environment)->getVal())), "Float", 0, 0, 0);
            return NULL;
        }
        else if (root->token->getVal() == "/=") {
            delete environment -> variables[root -> left -> token -> getVal()];
            environment -> variables[root -> left -> token -> getVal()] = new Token(to_string(stof(interp(root -> left, environment)->getVal()) / stof(interp(root -> right, environment)->getVal())), "Float", 0, 0, 0);
            return NULL;
        }
        else if (root->token->getVal() == "--") {
            delete environment -> variables[root -> left -> token -> getVal()];
            float newVal = stof(interp(root -> left, environment)->getVal()) - 1.0;
            environment -> variables[root -> left -> token -> getVal()] = new Token(to_string(newVal), "Float", 0, 0, 0);
            return NULL;
        }
        else if (root->token->getVal() == "++") {
            delete environment -> variables[root -> left -> token -> getVal()];
            float newVal = stof(interp(root -> left, environment)->getVal()) + 1.0;
            environment -> variables[root -> left -> token -> getVal()] = new Token(to_string(newVal), "Float", 0, 0, 0);
            return NULL;
        }

    } else if (root -> token -> getType() == "LogicalOperator") {
        // true and false tokens are created just to make the code easier to read
        int logic;
        Token True("1", "Float", 0,0,0), False("0", "Float", 0,0,0);
        Token *left, *right;
        left = interp(root -> left, environment);
        right = interp(root -> right, environment);
        // the following section is verbose but pretty self explanatory, the procedure is the same for each different logic operator
        if (root -> token -> getVal() == "<") {
            if (left -> getType() == "Float" && right -> getType() == "Float") {
                logic = stof(left -> getVal()) < stof(right -> getVal());
            } else {
                logic = left -> getVal() < right -> getVal();
            }
            if (logic) {
                result = &True;
            }
            else {
                result = &False;
            }
        } else if (root -> token -> getVal() == ">") {
            if (left -> getType() == "Float" && right -> getType() == "Float") {
                logic = stof(left -> getVal()) > stof(right -> getVal());
            } else {
                logic = left -> getVal() > right -> getVal();
            }
            if (logic) {
                result = &True;
            } else {
                result = &False;
            }
        } else if (root -> token -> getVal() == "!=") {
            if (left -> getType() == "Float" && right -> getType() == "Float") {
                logic = stof(left -> getVal()) != stof(right -> getVal());
            } else {
                logic = left -> getVal() != right -> getVal();
            }
            if (logic) {
                result = &True;
            } else {
                result = &False;
            }
        } else if (root -> token -> getVal() == "==") {
            if (left -> getType() == "Float" && right -> getType() == "Float") {
                logic = stof(left -> getVal()) == stof(right -> getVal());
            } else {
                logic = left -> getVal() == right -> getVal();
            }
            if (logic) {
                result = &True;
            } else {
                result = &False;
            }
        } else if (root -> token -> getVal() == "<=") {
            if (left -> getType() == "Float" && right -> getType() == "Float") {
                logic = stof(left -> getVal()) <= stof(right -> getVal());
            } else {
                logic = left -> getVal() <= right -> getVal();
            }
            if (logic) {
                result = &True;
            } else {
                result = &False;
            }
        } else if (root -> token -> getVal() == ">=") {
            if (left -> getType() == "Float" && right -> getType() == "Float") {
                logic = stof(left -> getVal()) >= stof(right -> getVal());
            } else {
                logic = left -> getVal() >= right -> getVal();
            }
            if (logic) {
                result = &True;
            } else {
                result = &False;
            }

        } else if (root -> token -> getVal() == "&&") {
            int left_int = stoi(interp(root -> left, environment)->getVal());
            int right_int = stoi(interp(root -> right, environment)->getVal());

            if (left_int && right_int) {
                result = &True;
            } else {
                result = &False;
            }
        } else if (root -> token -> getVal() == "||") {
            int left_int = stoi(interp(root -> left, environment)->getVal());
            int right_int = stoi(interp(root -> right, environment)->getVal());
            if (left_int || right_int) {
                result = &True;
            } else {
                result = &False;
            }
        }

    } else if (root -> token -> getType() == "Keyword") {
        // dealing with the different keywords
        // always return NULL in these functions because they dont print anything, they just calculate
        if (root -> token -> getVal() == "while") {
            while (true) {
                if (interp(root -> left, environment) -> getVal() == "1") {
                    Token *uselessToken = interp(root -> right, environment);
                } else {
                    break;
                }
            }
            return NULL;
        } else if (root -> token -> getVal() == "if") {
            cout << endl;
            if (interp(root -> left, environment) -> getVal() == "1") {
                Token *uselessToken = interp(root -> leftcenter, environment);
            } else if (root -> right) {
                Token *uselessToken = interp(root -> right, environment);
            }
            return NULL;
        } else if (root -> token -> getVal() == "for") {
            Token *variable = interp(root -> left, environment);
            while (true) {
                if (interp(root -> leftcenter, environment) -> getVal() == "1") {
                    Token *uselessToken = interp(root -> right, environment);
                    Token *increment = interp(root -> rightcenter, environment);
                } else {
                    break;
                }
            }
            return NULL;
        }
    }

    return result;
}
